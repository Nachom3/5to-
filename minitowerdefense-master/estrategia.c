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
//numero
void disponer_con_backtracking(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho; // Total de casillas posibles

    Coordenada posiciones_validas_torre[cantidad_casillas];// Lista de posiciones donde se puede poner una torre

    int casilla_elegida[cantidad_casillas];// Marca si ya usaste esa posición
    for (int i = 0; i < cantidad_casillas; i++) casilla_elegida[i] = 0;

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);// Llenamos el array con las posiciones válidas y cuántas hay

    // Creamos una pila para guardar los pasos
    Pila* pila = pila_crear();
    int numero_torres = 0; // cuántas torres llevamos colocadas

    int indices_por_torre[mapa->cant_torres]; // Guarda para cada torre cuál fue el índice de posición que estamos probando
    for (int i = 0; i < mapa->cant_torres; i++) indices_por_torre[i] = 0;

    while (numero_torres >= 0) {
        // Si ya colocamos todas las torres, terminamos
        if (numero_torres == mapa->cant_torres) {
            pila_destruir(pila);
            return;
        }

        int i = indices_por_torre[numero_torres]; // posición que estamos probando en este nivel
        int found = 0; // para saber si encontramos una posición válida

        while (i < cant_validas) {
            if (!casilla_elegida[i]) { // si no la usamos antes 
                Coordenada pos = posiciones_validas_torre[i];

                // Colocamos la torre en el mapa
                colocar_torre(mapa, pos.x, pos.y, numero_torres);
                casilla_elegida[i] = 1; // la marcamos como usada
                pila_apilar(pila, i); // guardamos esta elección

                // Avanzamos al siguiente nivel
                indices_por_torre[numero_torres] = i;
                numero_torres++;
                indices_por_torre[numero_torres] = 0; // empezamos desde 0 en el nuevo nivel
                found = 1;
                break;
            }
            i++; // probamos la siguiente posición
        }

        if (!found) {
            // No encontramos posición → hacemos backtracking
            if (numero_torres == 0) break; // no hay más atrás, se terminó

            numero_torres--; // volvemos al nivel anterior
            int last_i = pila_tope(pila); // recuperamos la última posición usada
            pila_desapilar(pila); // la sacamos de la pila

            // Quitamos la torre del mapa
            Coordenada pos = posiciones_validas_torre[last_i];
            mapa->casillas[pos.x][pos.y] = VACIO;
            casilla_elegida[last_i] = 0; // liberamos la posición

            // Probamos la siguiente opción en ese nivel
            indices_por_torre[numero_torres] = last_i + 1;
        }
    }

    pila_destruir(pila); // por si sale del while sin éxito
}

void disponer_custom(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    return;
}
