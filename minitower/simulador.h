#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "mapa.h"
#include "archivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int simular_nivel_rapido(Nivel *nivel, Mapa *mapa);
int simular_nivel_rapido2(Nivel *nivel, Mapa *mapa, Coordenada torres[mapa->cant_torres]); 
#endif
