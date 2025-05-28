#include "estrategia.h"
#include "mapa.h"
#include "nivel.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "simulador.h"
#include "pila.h"
#include "turno.h"
static int posiciones_validas(Coordenada *validas, TipoCasilla **casillas, int alto, int ancho) {
    int cant_posiciones_validas = 0;
    
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (casillas[i][j] == VACIO) {
                validas[cant_posiciones_validas].x = i;
                validas[cant_posiciones_validas++].y = j;
            }
        }
    }

    return cant_posiciones_validas;
}

static void limpiar_torres(Mapa* mapa) {
    for (int i = 0; i < mapa->alto; i++) {
        for (int j = 0; j < mapa->ancho; j++) {
            if (mapa->casillas[i][j] == TORRE)
                mapa->casillas[i][j] = VACIO;
        }
    }
}
static void colocar_torre(Mapa *mapa, int x, int y, int nro_torre) {
    // actualizar torre
    mapa->torres[nro_torre].x = x;
    mapa->torres[nro_torre].y = y;

    // actualizar mapa
    mapa->casillas[x][y] = TORRE;
}
static void quitar_torre(Mapa *mapa, int x, int y, int nro_torre) {
    // actualizar torre
    mapa->torres[nro_torre].x = -10;
    mapa->torres[nro_torre].y = -10;

    // actualizar mapa
    mapa->casillas[x][y] = VACIO;
}
static int determinar_posicion_torre(int *casilla_elegida, int cant_validas) {
    int nueva_posicion = rand() % cant_validas;
    while(casilla_elegida[nueva_posicion])
        nueva_posicion = rand() % cant_validas;

    return nueva_posicion;
}


void disponer(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int casilla_elegida[cantidad_casillas];
    for(int i = 0; i < cantidad_casillas; casilla_elegida[i++] = 0);

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
        int nueva_torre = determinar_posicion_torre(casilla_elegida, cant_validas);
        casilla_elegida[nueva_torre] = 1;
        int nueva_torre_x = posiciones_validas_torre[nueva_torre].x;
        int nueva_torre_y = posiciones_validas_torre[nueva_torre].y;
        colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
    }
}

static int buscar_indice(Coordenada coords[], int n, Coordenada buscada) {
    for (int i = 0; i < n; i++) {
        if (coords[i].x == buscada.x && coords[i].y == buscada.y) {
            return i;
        }
    }
    return -1;
}



void disponer_con_backtracking(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    
    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    if (cant_validas < mapa->cant_torres) {
        printf("No hay suficientes posiciones válidas para las torres\n");
        return;
    }

    int *usadas = calloc(cant_validas, sizeof(int)); // Usar calloc para inicializar en 0
    Pila *stack = pila_crear();
    int indiceActual = 0;
    
    while (1) { 
        if (stack->ultimo + 1 < mapa->cant_torres) {
            int encontrado = 0;
            
            while (indiceActual < cant_validas && !encontrado) {
                if (!usadas[indiceActual]) {
                    pila_apilar(stack, posiciones_validas_torre[indiceActual]);
                    usadas[indiceActual] = 1;
                    encontrado = 1;
                }
                indiceActual++;
            }

            if (!encontrado) {
                if (pila_es_vacia(stack)) {
                    free(usadas);
                    pila_destruir(stack);
                    printf("No hay solución posible\n");
                    return;
                }
                Coordenada ultima = pila_tope(stack);
                pila_desapilar(stack);
                
                int ultimo_indice = buscar_indice(posiciones_validas_torre, cant_validas, ultima);
                if (ultimo_indice != -1) {
                    usadas[ultimo_indice] = 0;
                }
                indiceActual = ultimo_indice + 1;
            }
        } else {
            Nivel nivelCopia = copiar_nivel(*nivel);
            Mapa mapaCopia = copiar_mapa(*mapa);
            
            limpiar_torres(&mapaCopia);
            
            // Colocar torres en la copia
            for (int i = 0; i < mapa->cant_torres; i++) {
                colocar_torre(&mapaCopia, stack->datos[i].x, stack->datos[i].y, i);
            }

            if(simular_nivel(&nivelCopia, &mapaCopia, disponer_con_backtracking) == 1) {
                // Encontramos solución válida
                *mapa = copiar_mapa(mapaCopia);
                for (int i = 0; i < mapa->cant_torres; i++) {
                    mapa->torres[i] = stack->datos[i];
                }
                
                free(usadas);
                pila_destruir(stack);
                liberar_nivel(&nivelCopia);
                liberar_mapa(&mapaCopia);
                return;
            }

            // Limpieza si no encontró solución
            liberar_nivel(&nivelCopia);
            liberar_mapa(&mapaCopia);

            // Backtrack
            Coordenada ultima = pila_tope(stack);
            pila_desapilar(stack);
            
            int ultimo_indice = buscar_indice(posiciones_validas_torre, cant_validas, ultima);
            if (ultimo_indice != -1) {
                usadas[ultimo_indice] = 0;
            }
            indiceActual = ultimo_indice + 1;
        }

        // Verificar si no quedan más combinaciones
        if (indiceActual >= cant_validas && pila_es_vacia(stack)) {
            free(usadas);
            pila_destruir(stack);
            printf("No hay solución posible\n");
            return;
        }
    }
}
void disponer_custom(Nivel* nivel, Mapa* mapa) {
    // implementación vacía o personalizada
}
