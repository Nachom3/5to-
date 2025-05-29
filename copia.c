int devolverNoUsada(Coordenada *coordenadas,int *bitmap, int cant_validas) {

    int posicion;
    for (int i = 0; i < cant_validas; i++) {
        if (!bitmap[i]) {
            posicion = i;
            bitmap[i] = 1; 
            return posicion;
        }
    }

    return -1;
}


void disponer_con_backtracking(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    int bitmap[cant_validas];
    Coordenada usadas[mapa->cant_torres]; // guarda las posiciones de las torres ya colocadas  

    int backtracking = 0; // contador de backtracking

    for(int i = 0; i < cant_validas; bitmap[i++] = 0);

    Pila *pila = pila_crear(); // Inicializar la pila
    for (int i = 0; i < mapa->cant_torres; i++) {
        pila_apilar(pila, posiciones_validas_torre[i]);
        usadas[i] = posiciones_validas_torre[i];
        bitmap[i] = 1; 
    }
    int gano = 0;

    while (!gano){
        Mapa *mapa_copia = copiar_mapa(mapa);
        Nivel *nivel_copia = copiar_nivel(nivel);
        for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
            int nueva_torre_x = pila->datos[colocadas].x;
            int nueva_torre_y = pila->datos[colocadas].y;
            colocar_torre(mapa_copia, nueva_torre_x, nueva_torre_y, colocadas);
        }
        if(simular_nivel2(nivel_copia, mapa_copia) == 1){
            gano = 1;
            mapa = copiar_mapa(mapa_copia);
            pila_destruir(pila);
        }   
        int posicion = devolverNoUsada(posiciones_validas_torre, bitmap, cant_validas);
        if (posicion != -1) { // si no hay mas posiciones validas
            pila_desapilar(pila);
            pila_apilar(pila, posiciones_validas_torre[posicion]);
            bitmap[mapa->cant_torres + backtracking +1] = 0;
        }else{
            Coordenada aux;
            for(int i = 0; i < mapa->cant_torres - backtracking; i++) {
                aux = posiciones_validas_torre[i];
                posiciones_validas_torre[i] = posiciones_validas_torre[i +1 + backtracking];
                posiciones_validas_torre[i + 1] = aux;
                backtracking++;
            }   
                  
        }
    }              
}
    
