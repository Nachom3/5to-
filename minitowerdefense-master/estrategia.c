#include "estrategia.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "simulador.h"
#include "pila.h"
typedef struct {
    Coordenada coord;
    int indice_posicion; // índice en posiciones_validas_torre
} EstadoTorre;

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

static void colocar_torre(Mapa *mapa, int x, int y, int nro_torre) {
    // actualizar torre
    mapa->torres[nro_torre].x = x;
    mapa->torres[nro_torre].y = y;

    // actualizar mapa
    mapa->casillas[x][y] = TORRE;
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

static void limpiar_torres(Mapa* mapa) {
    for (int i = 0; i < mapa->alto; i++) {
        for (int j = 0; j < mapa->ancho; j++) {
            if (mapa->casillas[i][j] == TORRE) {
                mapa->casillas[i][j] = VACIO;
            }
        }
    }
}
void disponer_con_backtracking(Nivel *nivel, Mapa* mapa) {
    int casillas_totales = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[casillas_totales];
    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    Pila *pila = pila_crear();
    int indices[MAX_PILA] = {0}; 
    int torre_actual = 0;

        while (torre_actual >= 0) {
        limpiar_torres(mapa); // Limpia SIEMPRE antes de cualquier intento

        for (int i = 0; i < torre_actual; i++)
            colocar_torre(mapa, pila->datos[i].x, pila->datos[i].y, i);

        printf("torre_actual: %d\n", torre_actual); 
        if (torre_actual == mapa->cant_torres) {
            if (simular_nivel(nivel, mapa, disponer_con_backtracking)) {
                pila_destruir(pila);
                return;
            }
            // Backtrack
            torre_actual--;
            pila_desapilar(pila);
            indices[torre_actual]++;
        } else if (indices[torre_actual] >= cant_validas) {
            indices[torre_actual] = 0;
            if (torre_actual == 0) 
            break;
            torre_actual--;
            pila_desapilar(pila);
            indices[torre_actual]++;
        } else {
            int repetida = 0;
            for (int j = 0; j < torre_actual; j++) {
                if (pila->datos[j].x == posiciones_validas_torre[indices[torre_actual]].x &&
                    pila->datos[j].y == posiciones_validas_torre[indices[torre_actual]].y) {
                    repetida = 1;
                    break;
                }
            }
            if (repetida) {
                indices[torre_actual]++;
            } else {
                pila_apilar(pila, posiciones_validas_torre[indices[torre_actual]]);
                torre_actual++;
                if (torre_actual < mapa->cant_torres)
                    indices[torre_actual] = 0;
            }
        }
    }
    pila_destruir(pila);
}

    void disponer_custom(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    return;
}
