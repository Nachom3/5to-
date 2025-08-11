# bot.py
import ccxt
import time
from datetime import datetime
import config
import scanner  # Importamos nuestros scripts como módulos
import manager


def main():
    print("--- INICIANDO BOT DE TRADING ---")

    # Creamos la conexión UNA SOLA VEZ
    exchange = ccxt.binance({
        'apiKey': config.API_KEY, 'secret': config.API_SECRET,
        'options': {'defaultType': 'future'}, 'enableRateLimit': True
    })
    # exchange.set_sandbox_mode(True) # DESCOMENTAR PARA USAR TESTNET
    exchange.options['warnOnFetchOpenOrdersWithoutSymbol'] = False

    print("Conexión con Binance establecida.")

    # El bucle infinito que controla el bot
    while True:
        try:
            print("\n" + "=" * 50)
            # 1. Ejecutar el scanner
            scanner.run_scanner(exchange)

            # 2. Ejecutar el manager
            manager.run_manager(exchange)

            # 3. Esperar antes del siguiente ciclo
            print(f"--- Ciclo completado. Esperando {config.MANAGER_SLEEP_TIME} segundos... ---")
            time.sleep(config.MANAGER_SLEEP_TIME)

        except KeyboardInterrupt:
            print("\nBot detenido manualmente. ¡Adiós!")
            break
        except Exception as e:
            print(f"ERROR CRÍTICO EN EL BUCLE PRINCIPAL: {e}")
            print("Reiniciando el ciclo en 60 segundos...")
            time.sleep(60)


if __name__ == "__main__":
    main()