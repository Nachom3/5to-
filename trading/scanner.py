# scanner.py
import ccxt
import pandas as pd
import numpy as np
import time
import os
from datetime import datetime
import config  # Importar nuestra configuración

# --- Constantes y Archivos de Estado ---
TIMESTAMP_FILE = "last_trade_timestamp.txt"


def get_last_trade_time():
    """Lee la marca de tiempo de la última operación desde el archivo."""
    if not os.path.exists(TIMESTAMP_FILE):
        return 0
    with open(TIMESTAMP_FILE, 'r') as f:
        try:
            return float(f.read().strip())
        except (ValueError, IOError):
            return 0


def set_last_trade_time():
    """Escribe la marca de tiempo actual en el archivo."""
    with open(TIMESTAMP_FILE, 'w') as f:
        f.write(str(time.time()))


def calculate_indicators(df):
    """Calcula RSI y Bandas de Bollinger y los añade al DataFrame."""
    # RSI
    delta = df['close'].diff()
    gain = (delta.where(delta > 0, 0)).rolling(window=config.RSI_PERIOD).mean()
    loss = (-delta.where(delta < 0, 0)).rolling(window=config.RSI_PERIOD).mean()
    if loss.eq(0).any():  # Evitar división por cero si no hay pérdidas
        rs = np.inf
    else:
        rs = gain / loss
    df['rsi'] = 100 - (100 / (1 + rs))

    # Bollinger Bands
    df['bb_mid'] = df['close'].rolling(window=config.BB_PERIOD).mean()
    std_dev = df['close'].rolling(window=config.BB_PERIOD).std()
    df['bb_upper'] = df['bb_mid'] + (std_dev * config.BB_STD_DEV)
    df['bb_lower'] = df['bb_mid'] - (std_dev * config.BB_STD_DEV)
    return df

# ... (todos los imports y las funciones auxiliares se quedan igual:
# get_last_trade_time, set_last_trade_time, calculate_indicators) ...

def run_scanner(exchange):
    """
    Función de búsqueda de oportunidades con la lógica de 2 velas consecutivas.
    """
    print(f"--- {datetime.now().strftime('%Y-%m-%d %H:%M:%S')} | Iniciando Scanner ---")

    last_trade_time = get_last_trade_time()
    if time.time() - last_trade_time < config.TRADE_COOLDOWN:
        print(
            f"COOLDOWN ACTIVO. No se buscarán nuevas posiciones. Esperando {config.TRADE_COOLDOWN - (time.time() - last_trade_time):.0f}s.")
        return

    try:
        positions = exchange.fetch_positions()
        symbols_with_positions = {p['info']['symbol'] for p in positions if float(p['info']['positionAmt']) != 0}

        if symbols_with_positions:
            print(f"Posiciones abiertas detectadas en: {', '.join(symbols_with_positions)}")
        else:
            print("No hay posiciones abiertas actualmente.")

        for pair in config.PAIRS:
            symbol = pair.replace('/', '')
            if symbol in symbols_with_positions:
                print(f"Saltando {pair}: ya hay una posición abierta.")
                continue

            print(f"Analizando {pair}...")
            ohlcv = exchange.fetch_ohlcv(pair, timeframe=config.TIMEFRAME, limit=100)
            if len(ohlcv) < config.BB_PERIOD + 2:  # Necesitamos al menos 2 velas para evaluar
                print(f"  -> No hay suficientes datos para analizar {pair}.")
                continue

            df = pd.DataFrame(ohlcv, columns=['timestamp', 'open', 'high', 'low', 'close', 'volume'])
            df = calculate_indicators(df)

            # --- MODIFICACIÓN CLAVE ---
            # Obtenemos las últimas dos velas completas.
            # La vela -1 es la actual (incompleta), la -2 es la última cerrada, la -3 es la anterior a esa.
            last_candle = df.iloc[-2]
            prev_candle = df.iloc[-3]

            # 4. Lógica de Entrada (con 2 velas)
            # Condición de VENTA (SHORT)
            # 1. Vela previa cerró por encima de su BB superior.
            # 2. Última vela cerrada también cerró por encima de su BB superior.
            # 3. RSI de la última vela cerrada está en sobrecompra.
            if (prev_candle['close'] > prev_candle['bb_upper'] and
                    last_candle['close'] > last_candle['bb_upper'] and
                    last_candle['rsi'] > config.RSI_OVERBOUGHT):

                print(f"¡SEÑAL DE VENTA (2 velas) DETECTADA PARA {pair}!")
                price = exchange.fetch_ticker(pair)['last']
                amount = config.ORDER_SIZE_USD / price
                exchange.set_leverage(config.LEVERAGE, symbol)
                order = exchange.create_market_sell_order(pair, amount)
                print("Orden de VENTA creada:", order)
                set_last_trade_time()
                return

            # Condición de COMPRA (LONG)
            # 1. Vela previa cerró por debajo de su BB inferior.
            # 2. Última vela cerrada también cerró por debajo de su BB inferior.
            # 3. RSI de la última vela cerrada está en sobreventa.
            elif (prev_candle['close'] < prev_candle['bb_lower'] and
                  last_candle['close'] < last_candle['bb_lower'] and
                  last_candle['rsi'] < config.RSI_OVERSOLD):

                print(f"¡SEÑAL DE COMPRA (2 velas) DETECTADA PARA {pair}!")
                price = exchange.fetch_ticker(pair)['last']
                amount = config.ORDER_SIZE_USD / price
                exchange.set_leverage(config.LEVERAGE, symbol)
                order = exchange.create_market_buy_order(pair, amount)
                print("Orden de COMPRA creada:", order)
                set_last_trade_time()
                return

        print("\n--- Búsqueda finalizada, no se encontraron nuevas oportunidades. ---")

    except Exception as e:
        print(f"Error en Scanner: {e}")