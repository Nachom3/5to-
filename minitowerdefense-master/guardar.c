void disponer_con_backtracking(Nivel *nivel, Mapa* mapa) {
    int casillas_totales = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[casillas_totales];
    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);
    int numero_torres = mapa->cant_torres;
    Pila *pila = pila_crear();
    Coordenada* usadas = malloc(sizeof(Coordenada) * cant_validas);
    for (int i = 0; i < cant_validas; i++) {
        usadas[i].x = -1; // Inicializar con coordenadas inválidas
        usadas[i].y = -1;
    }
    int torres_actual = 0;
    int gano = 0;

    while (gano == 0) { 
        limpiar_torres(mapa);
        for (int i = 0; i < numero_torres; i++){
            pila_apilar(pila, posiciones_validas_torre[i]);
            torres_actual++;
            usadas[i] = posiciones_validas_torre[i];
        }
        for(int i = 0; i < torres_actual; i++) {
            colocar_torre(mapa, pila->datos[i].x,pila->datos[i].y, i);
        }
        if (simular_nivel(nivel, mapa, disponer_con_backtracking) == 0) {
            gano = 1;
            break;
        }else{
            pila_desapilar(pila);
            torres_actual--;
            Coordenada ultima_torre = pila_tope(pila);
            int indice_ultima_torre = -1;
            for (int i = 0; i < cant_validas; i++) {
                if (usadas[i].x == -1 && usadas[i].y == -1) {
                    pila_apilar(pila, posiciones_validas_torre[i]);
                    torres_actual++;
                    usadas[i] = posiciones_validas_torre[i];
                }
            }
            usadas[indice_ultima_torre].x = -1; // Marcar como usada
            usadas[indice_ultima_torre].y = -1;

        }
    }   
}