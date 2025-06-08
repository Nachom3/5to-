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
static void colocar_torre(Mapa *mapa, int x, int y, int nro_torre) {
    // Actualizar posición de la torre
    mapa->torres[nro_torre].x = x;
    mapa->torres[nro_torre].y = y;

    // Actualizar el mapa
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


/*  Auxiliar: devuelve el índice de la coordenada c dentro del vector v
    (-1 si no está). Sirve para actualizar el bitmap cuando sacamos
    la última torre de la pila.                                                    */
static int indice_coord(Coordenada c, Coordenada v[], int n){
    for (int i = 0; i < n; i++)
        if (v[i].x == c.x && v[i].y == c.y) return i;
    return -1;
}

void disponer_con_backtracking(Nivel *nivel, Mapa *mapa){
    int  total = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[total];

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas,mapa->alto,mapa->ancho);

    int bitmap[cant_validas];
    for (int i = 0; i < cant_validas; i++) 
        bitmap[i] = 0;

    Pila *pila = pila_crear();
    for (int i = 0; i < mapa->cant_torres; i++) {
        pila_apilar(pila, posiciones_validas_torre[i]);
        bitmap[i] = 1;                       
    }

    int gano = 0;
    int NroBacktracks = 0;                     // *** cuánto “deslizamos” el array

    /* ───── 3. ciclo principal ───────────────────────────────────── */
    while (!gano) {
        Mapa* mapa_copia = copiar_mapa(mapa);
        Nivel* nivel_copia = copiar_nivel(nivel);

        for (int i = 0; i < mapa->cant_torres; i++)
            colocar_torre(mapa_copia, pila->datos[i].x, pila->datos[i].y, i);
        if (simular_nivel_rapido(nivel_copia, mapa_copia) == 1) {
            for (int i = 0; i < mapa->cant_torres; i++)
                colocar_torre(mapa, pila->datos[i].x, pila->datos[i].y,i);
            gano = 1;
        }
        liberar_mapa (mapa_copia);
        liberar_nivel(nivel_copia);
        if (gano) 
            break;

        /* 3-b  Generar la siguiente combinación -- usando
                la idea de «mover» el array de posiciones válidas     */

        /* quitar la última torre de la pila y des-marcarla en bitmap */
        Coordenada ultima = pila_tope(pila);
        pila_desapilar(pila);
        int posUltima = indice_coord(ultima,posiciones_validas_torre,cant_validas);
        if (posUltima != -1) 
            bitmap[posUltima] = 0;
        /* buscar la siguiente casilla libre después de posUltima     */
        int pos_nueva = -1;
        for (int i = posUltima + 1; i < cant_validas; i++)
            if (bitmap[i] == 0){ 
                pos_nueva = i; 
                break; 
            }

        if (pos_nueva != -1) {
            pila_apilar(pila, posiciones_validas_torre[pos_nueva]);/* hay otra casilla en la misma “ventana” */
            bitmap[pos_nueva] = 1;
        } else {
            /* se agotó la ventana actual  →  deslizamos el array     */
            NroBacktracks++;                       // ***
            if (NroBacktracks + mapa->cant_torres > cant_validas) {
                /* ya probamos todas las combinaciones posibles        */
                printf("No existe solución con la cantidad de torres dada\n");
                break;
            }

            /* mover la ventana una posición a la derecha             */
            Coordenada tmp = posiciones_validas_torre[0];
            for (int i = 0; i < cant_validas - 1; i++)
                posiciones_validas_torre[i] = posiciones_validas_torre[i+1];
            posiciones_validas_torre[cant_validas - 1] = tmp;

            /* reconstruir la pila + bitmap con la nueva ventana      */
            for (int i = 0; i < cant_validas; i++) 
                bitmap[i] = 0;
            pila->ultimo = -1;                  // vaciar pila

            for (int i = 0; i < mapa->cant_torres; i++) {
                pila_apilar(pila, posiciones_validas_torre[i]);
                bitmap[i] = 1;
            }
        }
    }

    pila_destruir(pila);
}

static int calidad_torre(Nivel* nivel, Mapa *mapa, Coordenada torre) {
    int distancia_ataque = mapa->distancia_ataque;
    int puntaje = 0;
    
    // Contamos caminos alcanzables
    for (int dx = -distancia_ataque; dx <= distancia_ataque; dx++) {
        for (int dy = -distancia_ataque; dy <= distancia_ataque; dy++) {
            if (abs(dx) + abs(dy) > distancia_ataque) continue; // Distancia Manhattan
            
            int nuevo_x = torre.x + dx;
            int nuevo_y = torre.y + dy;

            if (nuevo_x < 0 || nuevo_y < 0) continue;
            if (nuevo_x >= mapa->alto || nuevo_y >= mapa->ancho) continue;
            
            // Puntos por caminos encontrados
            if(mapa->casillas[nuevo_x][nuevo_y] == CAMINO) {
                int distancia = abs(dx) + abs(dy);
                puntaje += 10 * (distancia_ataque - distancia + 1); // Más puntos a casillas cercanas
            }
            
            // Penalización por torres cercanas
            if(mapa->casillas[nuevo_x][nuevo_y] == TORRE) {
                puntaje -= 15; // Penalización por solapamiento
            }
        }
    }
    
    // Bonus por posición central
    int distancia_centro_x = abs(torre.x - mapa->alto/2);
    int distancia_centro_y = abs(torre.y - mapa->ancho/2);
    puntaje += 3 * (mapa->alto/2 - distancia_centro_x);
    puntaje += 3 * (mapa->ancho/2 - distancia_centro_y);
    
    return puntaje;
}

void disponer_custom(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int calidades[cantidad_casillas];  // Array para almacenar calidades

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);
    
    // Calculamos y almacenamos las calidades
    for (int i = 0; i < cant_validas; i++) {
        calidades[i] = calidad_torre(nivel, mapa, posiciones_validas_torre[i]);
    }

    // Ordenamiento por inserción (más eficiente que bubble sort para arrays pequeños)
    for (int i = 1; i < cant_validas; i++) {
        Coordenada coord_actual = posiciones_validas_torre[i];
        int calidad_actual = calidades[i];
        int j = i - 1;
        
        while (j >= 0 && calidades[j] < calidad_actual) {
            posiciones_validas_torre[j + 1] = posiciones_validas_torre[j];
            calidades[j + 1] = calidades[j];
            j--;
        }
        
        posiciones_validas_torre[j + 1] = coord_actual;
        calidades[j + 1] = calidad_actual;
    }

    // Colocamos las torres en las mejores posiciones
    for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
        int nueva_torre_x = posiciones_validas_torre[colocadas].x;
        int nueva_torre_y = posiciones_validas_torre[colocadas].y;
        colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
        
        // Recalculamos calidades después de colocar cada torre
        if (colocadas < mapa->cant_torres - 1) {
            for (int i = colocadas + 1; i < cant_validas; i++) {
                calidades[i] = calidad_torre(nivel, mapa, posiciones_validas_torre[i]);
            }
            
            // Reordenamos las posiciones restantes
            for (int i = colocadas + 2; i < cant_validas; i++) {
                Coordenada coord_actual = posiciones_validas_torre[i];
                int calidad_actual = calidades[i];
                int j = i - 1;
                
                while (j > colocadas && calidades[j] < calidad_actual) {
                    posiciones_validas_torre[j + 1] = posiciones_validas_torre[j];
                    calidades[j + 1] = calidades[j];
                    j--;
                }
                
                posiciones_validas_torre[j + 1] = coord_actual;
                calidades[j + 1] = calidad_actual;
            }
        }
    }
}