#include "nivel.h"

static Camino *inicializar_camino(int largo_camino) {
    Camino *camino = malloc(sizeof(Camino));
    camino->posiciones = malloc(sizeof(Coordenada) * largo_camino);
    camino->largo_camino = largo_camino;

    return camino;
}

static void mostrar_camino(Camino *camino) {
    printf("Camino:\n");
    for (int i = 0; i < camino->largo_camino; i++)
        printf("x: %d  - y: %d\n", camino->posiciones[i].x, camino->posiciones[i].y);
}

static void liberar_camino(Camino *camino) {
    free(camino->posiciones);
    free(camino);
}

static Enemigos *inicializar_enemigos(int cant_enemigos, int vida_inicial) {
    Enemigos *enemigos = malloc(sizeof(Enemigos));

    enemigos->vida = malloc(sizeof(int) * cant_enemigos);
    enemigos->activos = malloc(sizeof(int) * cant_enemigos);
    enemigos->posiciones = malloc(sizeof(Coordenada) * cant_enemigos);

    enemigos->cantidad = cant_enemigos;
    enemigos->cantidad_activos = cant_enemigos;
    enemigos->vida_inicial = vida_inicial;

    for (int i = 0; i < cant_enemigos; i++) {
        enemigos->posiciones[i].x = enemigos->posiciones[i].y = -1;
        enemigos->vida[i] = vida_inicial;
        enemigos->activos[i] = 1;
    }
    
    return enemigos;
}

void mostrar_enemigos(Enemigos *enemigos) {
    printf("Cantidad enemigos: %d - Cantidad enemigos activos: %d\n",
        enemigos->cantidad, enemigos->cantidad_activos);
    for (int i = 0; i < enemigos->cantidad; i++) {
        printf("x: %d  - y: %d\n", enemigos->posiciones[i].x, enemigos->posiciones[i].y);
        printf("vida: %d - activo: %d\n", enemigos->vida[i], enemigos->activos[i]);
    }
}

static void liberar_enemigos(Enemigos* enemigos) {
    free(enemigos->vida);
    free(enemigos->activos);
    free(enemigos->posiciones);
    free(enemigos);
}

void mostrar_nivel(Nivel *nivel) {
    mostrar_camino(nivel->camino);
    mostrar_enemigos(nivel->enemigos);
}

Nivel *inicializar_nivel(int largo_camino, int cant_enemigos, int vida_inicial) {
    Nivel *nivel = malloc(sizeof(Nivel));
    nivel->camino = inicializar_camino(largo_camino);
    nivel->enemigos = inicializar_enemigos(cant_enemigos, vida_inicial);
    return nivel;
}

void liberar_nivel(Nivel *nivel) {
    liberar_camino(nivel->camino);
    liberar_enemigos(nivel->enemigos);
    free(nivel);
}

Nivel* copiar_nivel(Nivel* original) {
    // Asignar memoria para la copia
    Nivel* copia = malloc(sizeof(Nivel));
    if (!copia) {
        printf("Error: No se pudo asignar memoria para la copia del nivel.\n");
        return NULL;
    }

    // Copiar valores simples
    *copia = *original;

    // Copiar enemigos
    copia->enemigos = malloc(sizeof(Enemigos));
    if (!copia->enemigos) {
        printf("Error: No se pudo asignar memoria para los enemigos.\n");
        free(copia);
        return NULL;
    }
    *copia->enemigos = *original->enemigos;

    int cant = original->enemigos->cantidad;

    copia->enemigos->posiciones = malloc(cant * sizeof(Coordenada));
    if (!copia->enemigos->posiciones) {
        printf("Error: No se pudo asignar memoria para las posiciones de los enemigos.\n");
        free(copia->enemigos);
        free(copia);
        return NULL;
    }
    memcpy(copia->enemigos->posiciones, original->enemigos->posiciones, cant * sizeof(Coordenada));

    copia->enemigos->vida = malloc(cant * sizeof(int));
    if (!copia->enemigos->vida) {
        printf("Error: No se pudo asignar memoria para las vidas de los enemigos.\n");
        free(copia->enemigos->posiciones);
        free(copia->enemigos);
        free(copia);
        return NULL;
    }
    memcpy(copia->enemigos->vida, original->enemigos->vida, cant * sizeof(int));

    copia->enemigos->activos = malloc(cant * sizeof(int));
    if (!copia->enemigos->activos) {
        printf("Error: No se pudo asignar memoria para los enemigos activos.\n");
        free(copia->enemigos->vida);
        free(copia->enemigos->posiciones);
        free(copia->enemigos);
        free(copia);
        return NULL;
    }
    memcpy(copia->enemigos->activos, original->enemigos->activos, cant * sizeof(int));

    // Copiar camino
    copia->camino = malloc(sizeof(Camino));
    if (!copia->camino) {
        printf("Error: No se pudo asignar memoria para el camino.\n");
        free(copia->enemigos->activos);
        free(copia->enemigos->vida);
        free(copia->enemigos->posiciones);
        free(copia->enemigos);
        free(copia);
        return NULL;
    }
    *copia->camino = *original->camino;

    copia->camino->posiciones = malloc(original->camino->largo_camino * sizeof(Coordenada));
    if (!copia->camino->posiciones) {
        printf("Error: No se pudo asignar memoria para las posiciones del camino.\n");
        free(copia->camino);
        free(copia->enemigos->activos);
        free(copia->enemigos->vida);
        free(copia->enemigos->posiciones);
        free(copia->enemigos);
        free(copia);
        return NULL;
    }
    memcpy(copia->camino->posiciones, original->camino->posiciones, original->camino->largo_camino * sizeof(Coordenada));

    return copia;
}