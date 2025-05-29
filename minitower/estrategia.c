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
    /* A cargo de la/el estudiante */
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    
    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    int usadas[cant_validas]; // Bitmap de coordenadas usadas (0 para false, 1 para true)
    Pila *stack = pila_crear();
    int indiceActual = 0;
    
    for (int i = 0; i < cant_validas; i++) {
        usadas[i] = 0; 
    }
    int funciono = 0;
    /*Nivel *nivelCopia = inicializar_nivel(nivel->camino->largo_camino, nivel->enemigos->cantidad, nivel->enemigos->vida_inicial);*/
    /*Mapa *mapaCopia = inicializar_mapa(mapa->ancho, mapa->alto, mapa->cant_torres, mapa->distancia_ataque);*/
    /**/
    while (!funciono) { 
        // Paso 1: Intentar agregar una nueva coordenada al stack
        if (stack->ultimo+1 < mapa->cant_torres) { 
            int encontrado = 0; 
            
            // Buscamos la próxima coordenada disponible
            for (int i = indiceActual; i < cant_validas; i++) {
                if (usadas[i] == 0) { 
                    pila_apilar(stack, posiciones_validas_torre[i]);
                    usadas[i] = 1; 
                    indiceActual = i + 1;
                    encontrado = 1;
                    break;
                }
            }

            if (encontrado == 0) { // Si no se encontró una nueva coordenada
                // No hay más coordenadas disponibles, hacemos backtrack

                if (pila_es_vacia(stack)) {
                    pila_destruir(stack);
                    printf("no hay ninguna solucion\n");
                    funciono = 1;
                    return;
                }

                Coordenada ultima = pila_tope(stack);
                pila_desapilar(stack);
                // Buscamos su índice
                int ultimo_indice = buscar_indice(posiciones_validas_torre, cant_validas, ultima);

                if (ultimo_indice != -1) { 
                   usadas[ultimo_indice] = 0;
                }
                indiceActual = ultimo_indice + 1;
            }
        }
        else {
            //aca evaluamos las torres en el stack, si funciona, terminar.
            /*copiar_nivel(nivelCopia, nivel);*/
            /*copiar_mapa(mapaCopia, mapa);*/
            Coordenada torres[mapa->cant_torres];
            for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
                int nueva_torre_x = stack->datos[colocadas].x;
                int nueva_torre_y = stack->datos[colocadas].y;
                torres[colocadas].x = nueva_torre_x;
                torres[colocadas].y = nueva_torre_y;
                /*colocar_torre(mapaCopia, nueva_torre_x, nueva_torre_y, colocadas);*/
            }
            if(simular_nivel_rapido2(nivel, mapa, torres) == 1){
                funciono = 1;
                for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
                    int nueva_torre_x = stack->datos[colocadas].x;
                    int nueva_torre_y = stack->datos[colocadas].y;
                    colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
                }
                pila_destruir(stack);
            }            // Hacemos backtrack si la combinación no es válida


            if(funciono == 0){
                Coordenada ultima = pila_tope(stack);
                pila_desapilar(stack);
            
                int ultimo_indice = buscar_indice(posiciones_validas_torre, cant_validas, ultima);
                if (ultimo_indice != -1) {
                    usadas[ultimo_indice] = 0; // 0 para 'false'
                }
                indiceActual = ultimo_indice + 1;
            }
        }
    }

    /*liberar_nivel(nivelCopia);*/
    /*liberar_mapa(mapaCopia);*/
}



void disponer_custom(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    // ordeno las posiciones validas de torres segun su calidad.
    for (int i = 0; i< cant_validas-1;i++){
        for (int j = 0;j<cant_validas-i-1; j++){
            if(calidad_torre(nivel, mapa, posiciones_validas_torre[j]) < calidad_torre(nivel, mapa, posiciones_validas_torre[j+1])){
                //swap
                Coordenada aux = posiciones_validas_torre[j];
                posiciones_validas_torre[j] = posiciones_validas_torre[j+1];
                posiciones_validas_torre[j+1] = aux;
            }
        }
    }
    //esto es para probar, despues comentar.
    for(int i = 0; i<cant_validas; i++){
        printf("%i, ", calidad_torre(nivel, mapa, posiciones_validas_torre[i]));
    }
    //de la lista ordenada, coloco las primeras/mejores torres.
    for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
        int nueva_torre_x = posiciones_validas_torre[colocadas].x;
        int nueva_torre_y = posiciones_validas_torre[colocadas].y;
        colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
    }
    return;
}

int calidad_torre(Nivel* nivel, Mapa *mapa, Coordenada torre){
    //calcula cuantos caminos ve y ataca cada torre.
    int distancia_ataque = mapa->distancia_ataque;
    int count = 0;
    for (int dx = -distancia_ataque; dx <= distancia_ataque; dx++) {
        for (int dy = -distancia_ataque; dy <= distancia_ataque; dy++) {
            int nuevo_x = torre.x + dx;
            int nuevo_y = torre.y + dy;

            if (dx == 0 && dy == 0) continue;
            if (nuevo_x < 0 || nuevo_y < 0) continue;
            if (nuevo_x >= mapa->alto || nuevo_y >= mapa->ancho) continue;
            
            if(mapa->casillas[nuevo_x][nuevo_y] == CAMINO) {
                count++;
            }
        }
    } 
    return count;
}

