#ifndef TURNO_H
#define TURNO_H

#include "mapa.h"
#include "estrategia.h"
int simular_turno(Mapa *mapa, Nivel *nivel, Coordenada*, int);
void inicializar_turno_backtracking(Nivel *nivel, Mapa *mapa);
int buscarEnemigo(Coordenada*, int, Coordenada);

void inicializar_turno(Nivel *nivel, Mapa *mapa, DisposicionTorres estrategia);

#endif
