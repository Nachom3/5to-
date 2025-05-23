#include "estrategia.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "simulador.h"
#include "pila.h"

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

void disponer_con_backtracking(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int casilla_elegida[cantidad_casillas];
    for (int i = 0; i < cantidad_casillas; i++) casilla_elegida[i] = 0;

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    Pila* pila = pila_crear();
    int nivel_actual = 0;

    // Este array guarda por cada nivel el índice actual que estamos probando
    int indices_por_nivel[mapa->cant_torres];
    for (int i = 0; i < mapa->cant_torres; i++) indices_por_nivel[i] = 0;

    while (nivel_actual >= 0) {
        // Si ya colocaste todas las torres
        if (nivel_actual == mapa->cant_torres) {
            // Disposición completa lista
            pila_destruir(pila);
            return;
        }

        int index = indices_por_nivel[nivel_actual];
        int found = 0;

        while (index < cant_validas) {
            if (!casilla_elegida[index]) {
                Coordenada pos = posiciones_validas_torre[index];
                colocar_torre(mapa, pos.x, pos.y, nivel_actual);
                casilla_elegida[index] = 1;
                pila_apilar(pila, index);
                indices_por_nivel[nivel_actual] = index; // lo que pusiste en este nivel
                nivel_actual++;
                indices_por_nivel[nivel_actual] = 0;     // arranca desde 0 en el nuevo nivel
                found = 1;
                break;
            }
            index++;
        }

        if (!found) {
            // No hay más opciones en este nivel → backtrack
            if (nivel_actual == 0) break; // ya no hay nada que desapilar

            nivel_actual--;
            int last_index = pila_tope(pila);
            pila_desapilar(pila);
            Coordenada pos = posiciones_validas_torre[last_index];
            mapa->casillas[pos.x][pos.y] = VACIO;
            casilla_elegida[last_index] = 0;
            indices_por_nivel[nivel_actual] = last_index + 1; // probar siguiente posición
        }
    }

    pila_destruir(pila);
}

void disponer_custom(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    return;
}
