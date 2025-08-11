# manager.py
import ccxt
import time
# No necesitamos subprocess ni sys aquí
from datetime import datetime
import config


def run_manager(exchange):
    """
    Función completa de gestión de posiciones y órdenes.
    Es llamada por el script orquestador bot.py.
    """
    print(f"--- {datetime.now().strftime('%Y-%m-%d %H:%M:%S')} | Iniciando Manager ---")

    try:
        # 1. OBTENER ESTADO ACTUAL DEL EXCHANGE
        all_positions = exchange.fetch_positions()
        # Pedimos todas las órdenes abiertas. La advertencia ya está suprimida en bot.py
        open_orders = exchange.fetch_open_orders()

        open_positions = [p for p in all_positions if float(p['info']['positionAmt']) != 0]
        symbols_with_positions = {p['symbol'] for p in open_positions}

        # 2. GESTIONAR POSICIONES ABIERTAS (LÓGICA COMPLETA RESTAURADA)
        for pos in open_positions:
            symbol, side = pos['symbol'], pos['side']
            entry_price = float(pos['entryPrice'])
            pos_size = abs(float(pos['contracts']))

            print(f"\nGestionando {symbol}: Lado={side.upper()}, Tamaño={pos_size}, Entrada={entry_price}")
            related_orders = [o for o in open_orders if o['symbol'] == symbol]

            # Lógica para determinar si la posición está promediada
            initial_size_approx = config.ORDER_SIZE_USD / entry_price
            # Si el tamaño actual es mayor que el tamaño inicial + el tamaño de promedio (con un pequeño margen de error)
            is_averaged = pos_size > (initial_size_approx * (1 + config.AVERAGING_MULTIPLIER - 0.1))

            if is_averaged:
                print("  -> Posición detectada como PROMEDIADA.")

                # --- PASO 1: DEFINIR LOS PRECIOS OBJETIVO ---
                # Calculamos cuáles deberían ser los precios correctos para el SL y el TP
                expected_sl_price = round(
                    entry_price * (1 - config.AVERAGED_SL_PERCENTAGE) if side == 'long' else entry_price * (
                                1 + config.AVERAGED_SL_PERCENTAGE), 4)
                expected_tp_price = round(
                    entry_price * (1 + config.AVERAGED_TP_PERCENTAGE) if side == 'long' else entry_price * (
                                1 - config.AVERAGED_TP_PERCENTAGE), 4)

                # --- PASO 2: REVISAR ÓRDENES EXISTENTES Y CANCELAR LAS INCORRECTAS ---
                sl_exists = False
                tp_exists = False

                for order in related_orders:
                    order_price = round(float(order['info'].get('stopPrice', 0)), 4)

                    # Cancelar cualquier orden LÍMITE (sobrante de la etapa inicial)
                    if order['type'] == 'limit':
                        print(f"  -> Limpiando orden de promedio obsoleta (ID: {order['id']}).")
                        try:
                            exchange.cancel_order(order['id'], symbol); continue
                        except Exception as e:
                            print(f"    -> Error al cancelar: {e}")

                    # Revisar si el SL es correcto
                    if order['type'] == 'stop_market' and order_price == expected_sl_price:
                        sl_exists = True
                    elif order['type'] == 'stop_market' and order_price != expected_sl_price:
                        print(
                            f"  -> SL incorrecto encontrado (Precio: {order_price}, Esperado: {expected_sl_price}). Cancelando.")
                        try:
                            exchange.cancel_order(order['id'], symbol)
                        except Exception as e:
                            print(f"    -> Error al cancelar: {e}")

                    # Revisar si el TP es correcto
                    if order['type'] == 'take_profit_market' and order_price == expected_tp_price:
                        tp_exists = True
                    elif order['type'] == 'take_profit_market' and order_price != expected_tp_price:
                        print(
                            f"  -> TP incorrecto encontrado (Precio: {order_price}, Esperado: {expected_tp_price}). Cancelando.")
                        try:
                            exchange.cancel_order(order['id'], symbol)
                        except Exception as e:
                            print(f"    -> Error al cancelar: {e}")

                # --- PASO 3: CREAR ÓRDENES SOLO SI FALTAN ---
                if not sl_exists:
                    params = {'stopPrice': expected_sl_price, 'reduceOnly': True}
                    exchange.create_order(symbol, 'stop_market', 'sell' if side == 'long' else 'buy', pos_size, None,
                                          params)
                    print(f"  -> Creado SL para posición promediada en {expected_sl_price}")

                if not tp_exists:
                    params = {'stopPrice': expected_tp_price, 'reduceOnly': True}
                    exchange.create_order(symbol, 'take_profit_market', 'sell' if side == 'long' else 'buy', pos_size,
                                          None, params)
                    print(f"  -> Creado TP para posición promediada en {expected_tp_price}")

                if sl_exists and tp_exists:
                    print("  -> SL y TP correctos ya están en su lugar. No se necesita ninguna acción.")

            else:  # POSICIÓN INICIAL
                print("  -> Posición detectada como INICIAL.")
                has_tp = any(o['type'] == 'take_profit_market' for o in related_orders)
                has_avg_order = any(o['type'] == 'limit' for o in related_orders)

                if not has_tp:
                    tp_price = entry_price * (1 + config.INITIAL_TP_PERCENTAGE) if side == 'long' else entry_price * (
                                1 - config.INITIAL_TP_PERCENTAGE)
                    params = {'stopPrice': tp_price, 'reduceOnly': True}
                    exchange.create_order(symbol, 'take_profit_market', 'sell' if side == 'long' else 'buy', pos_size,
                                          None, params)
                    print(f"  -> Creado TP inicial en {tp_price:.4f}")

                if not has_avg_order:
                    avg_price = entry_price * (
                                1 - config.AVERAGING_DISTANCE_PERCENTAGE) if side == 'long' else entry_price * (
                                1 + config.AVERAGING_DISTANCE_PERCENTAGE)
                    avg_amount = pos_size * config.AVERAGING_MULTIPLIER
                    order_side = 'buy' if side == 'long' else 'sell'
                    exchange.create_limit_order(symbol, order_side, avg_amount, avg_price)
                    print(
                        f"  -> Creada orden de promedio en {avg_price:.4f} por {avg_amount:.4f} {symbol.replace('/USDT', '')}")

        # 3. LIMPIAR ÓRDENES HUÉRFANAS (LÓGICA COMPLETA RESTAURADA)
        print("\nBuscando órdenes huérfanas...")
        cleaned_count = 0
        for order in open_orders:
            if order['symbol'] not in symbols_with_positions:
                try:
                    exchange.cancel_order(order['id'], order['symbol'])
                    print(f"  -> Cancelada orden huérfana ID {order['id']} para {order['symbol']}")
                    cleaned_count += 1
                except Exception as e:
                    print(f"  -> Error cancelando orden huérfana ID {order['id']}: {e}")
        if cleaned_count == 0: print("  -> No se encontraron órdenes huérfanas.")

    except Exception as e:
        print(f"Error en Manager: {e}")