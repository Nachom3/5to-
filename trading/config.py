# config.py

# --- Claves API de Binance ---
# ¡¡MUY IMPORTANTE!! COMIENZA USANDO LAS CLAVES DE LA TESTNET.

#API_KEY = "api no secret"
#API_SECRET = "aca va mi api secret"
# Para usar Testnet, hay una línea que debes descomentar en scanner.py y manager.py

# --- Configuración del Scanner (Script 1) ---
PAIRS = ['AAVE/USDT', 'ALGO/USDT', 'AVAX/USDT', 'ARB/USDT', 'APT/USDT', 'ATOM/USDT', 'AERO/USDT', 'ADA/USDT',
         'BATUSDT', 'BCH/USDT', 'BTC/USDT', 'BNB/USDT', 'CAKE/USDT', 'CRV/USDT', 'CFX/USDT',
         'DOGE/USDT', 'DOT/USDT', 'DASHUSDT', 'DOLOUSDT', 'ENA/USDT', 'ETC/USDT', 'ENS/USDT', 'ETH/USDT', 'EIGENUSDT',
         'FET/USDT', 'FIL/USDT', 'GRT/USDT', 'HYPE/USDT', 'HBAR/USDT',
         'ICP/USDT', 'INJ/USDT', 'IOTA/USDT', 'IMXUSDT', 'INITUSDT',
         'JUP/USDT', 'JTO/USDT', 'KAS/USDT', 'LINK/USDT', 'LTC/USDT', 'LDO/USDT',
         'MAV/USDT', 'MAGICUSDT', 'NEAR/USDT', 'OP/USDT', 'ONDO/USDT', 'ORDI/USDT', 'OMUSDT', 'ONTUSDT',
         'POL/USDT', 'PENDLE/USDT', 'PUMPUSDT', 'QNT/USDT', 'RENDER/USDT',
         'STX/USDT', 'SUI/USDT', 'SPX/USDT', 'S/USDT', 'SOL/USDT', 'SEIUSDT', 'STXUSDT', 'SPKUSDT',
         'TIA/USDT', 'TRB/USDT', 'TON/USDT', 'TAO/USDT', 'TRX/USDT', 'THETAUSDT',
         'UNI/USDT', 'VIRTUAL/USDT', 'VETUSDT', 'VINEUSDT', 'WCT/USDT', 'WLD/USDT', 'WIF/USDT',
         'XLM/USDT', 'XMR/USDT', 'XRP/USDT', 'XTZUSDT', 'ZECUSDT']

TIMEFRAME = '1m'          # Timeframe para el análisis de velas
ORDER_SIZE_USD = 10.0     # Tamaño de la posición inicial en USD
LEVERAGE = 10             # Nivel de apalancamiento

# Parámetros de los indicadores
RSI_PERIOD = 14
RSI_OVERBOUGHT = 70
RSI_OVERSOLD = 30
BB_PERIOD = 20
BB_STD_DEV = 2.0

# Cooldown en segundos después de abrir una posición
TRADE_COOLDOWN = 120  # 2 minutos

# --- Configuración del Manager (Script 2) ---
# Porcentajes (ej: 0.01 = 1%)
INITIAL_TP_PERCENTAGE = 0.01          # 1% Take Profit para la posición inicial
AVERAGING_DISTANCE_PERCENTAGE = 0.01  # 1% de distancia para colocar la orden de promedio
AVERAGING_MULTIPLIER = 1.5            # La orden de promedio será 1.5 veces el tamaño inicial

# Gestión después de promediar
AVERAGED_SL_PERCENTAGE = 0.01   # 1% Stop Loss después de promediar
AVERAGED_TP_PERCENTAGE = 0.005  # 0.5% Take Profit después de promediar

# --- Configuración del Bucle ---
MANAGER_SLEEP_TIME = 30  # Segundos que espera el manager antes de llamar al scanner