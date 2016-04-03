#include "laberinto.h"

// Camino = 0
// Paredes = 1

/* Arreglo dinamico, comportamiento como pila */
pilaD arregloDin() {
    pilaD arrD;
    arrD.elementos = NULL;
    arrD.nElementos = 0;
    return arrD;
}

// Agregar al final.
void arrPush(pilaD* arrD, coord equisye) {
    arrD->elementos = realloc(arrD->elementos, (int) (arrD->nElementos + 1) * sizeof (coord*));
    arrD->elementos[arrD->nElementos] = equisye;
    arrD->nElementos++;
}

// Eliminar el ultimo elemento.
void arrPop(pilaD* arrD) {
    arrD->elementos = realloc(arrD->elementos, (arrD->nElementos - 1) * sizeof (coord));
    arrD->nElementos--;
}

// Liberar memoria.
void arrFree(pilaD* arrD) {
    free(arrD->elementos);
    arrD->elementos = NULL;
    arrD->nElementos = 0;
}
/* Fin arreglo dinamico */

/* Laberinto */

/* Generar laberinto */
laberinto genLab(char const *nombreArc, int iColumna, int iRenglon) {
    int renglones = 1, columnas = 0; // Conteo de renglones y columnas.
    int i, j, conteo = 1; // Conteo -> Si ya se contaron las columnas, ya no seguir contandolas || Conteo para las salidas.
    int s; // Conteo de salidas.
    int c; // Lectura de caracter.
    FILE *archivo;
    laberinto labtmp;

    archivo = fopen(nombreArc, "r");
    if (archivo == NULL) {
        printf("Archivo inexistente.\n");
        exit(EXIT_FAILURE);
    }

    c = fgetc(archivo);
    // Contabilizar columnas y renglones para reservar memoria.
    // c=32 -> espacio en blanco || c=10 & c=13 -> salto de linea
    while (!feof(archivo)) {
        if (c != 32 && c != 10 && c != 13 && conteo == 1) // Conteo de caracteres mientras no sean espacios o saltos de linea.
            columnas++;
        if (c == 10) { // Conteo de saltos de linea para saber los renglones,
            renglones++;
            conteo = 0;
        }
        c = fgetc(archivo);
    }

    labtmp.camino = (int**) malloc(renglones * sizeof (int*));
    if (labtmp.camino != NULL) {
        for (i = 0; i < renglones; i++) {
            labtmp.camino[i] = (int*) malloc(columnas * sizeof (int));
            if (labtmp.camino[i] == NULL) {
                printf("No se pudo reservar la memoria\n");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        printf("No se pudo reservar la memoria\n");
        exit(EXIT_FAILURE);
    }

    fseek(archivo, 0, SEEK_SET); // Volver al inicio del archivo.
    c = fgetc(archivo);
    i = j = 0;
    labtmp.nSalidas = 0;

    // Generar laberinto & detectar salidas.
    while (!feof(archivo)) {
        if (c == 10) // Si se dettecta un salto de linea, hay nuevo renglon.
            i++;
        if (c != 32 && c != 10 && c != 13) { // Mientras no sea un salto de linea o un espacio se guarda en el arreglo.
            labtmp.camino[i][j] = (int) c - 48; // De char a int.
            if ((i == 0 || j == 0 || i == renglones - 1 || j == columnas - 1) && ((int) c - 48 == 0)) { // Detectar posibles salidas.
                labtmp.nSalidas += 1;
            }
            j++;
            if (j == columnas)
                j = 0;
        }
        c = fgetc(archivo);

    }
    fclose(archivo);

    if (labtmp.nSalidas == 0) {
        printf("El laberinto no tendra solucion, no exise ninguna salida.\n");
        exit(EXIT_FAILURE);
    }

    labtmp.renglones = renglones; // Renglones (x) del laberinto.
    labtmp.columnas = columnas; // Columnas (y) del laberinto.

    if (iRenglon < 0 || iRenglon >= renglones || iColumna < 0 || iColumna >= columnas) { // Evitar violacion de segmento.
        printf("La salida no es valida.\n");
        exit(EXIT_FAILURE);
    }

    if (labtmp.camino[iRenglon][iColumna] == 0) { // Asegurar que se trata de un camino y no una pared.
        labtmp.inicio.renglon = iRenglon;
        labtmp.inicio.columna = iColumna;
    } else {
        printf("La salida no es valida, corresponde a una pared.\n");
        exit(EXIT_FAILURE);
    }

    return labtmp;
}

void imprimirL(laberinto nuevoL) {
    printf("Inicio: x=%i  y=%i\n", nuevoL.inicio.renglon, nuevoL.inicio.columna);
    printf("Posibles salidas: %i\n", nuevoL.nSalidas);
    int i, j;
    for (i = 0; i < nuevoL.renglones; i++) {
        for (j = 0; j < nuevoL.columnas; j++) {
            if (nuevoL.camino[i][j] == 0)
                printf(".");
            else
                printf("%c", 177); // pared
        }
        printf("\n");
    }
    printf("\n");
}

void freeL(laberinto freeL) {
    free(freeL.camino);
    freeL.camino = NULL;
}

/* Resolucion de laberinto */
coord posibleCelda(laberinto nuevoL, coord celdaActual, pilaD* visitada) {
    coord celdaPosible;

    // Derecha.
    celdaPosible.renglon = celdaActual.renglon;
    celdaPosible.columna = (celdaActual.columna) + 1;
    if (((celdaPosible.renglon < nuevoL.renglones && celdaPosible.renglon >= 0) && (celdaPosible.columna < nuevoL.columnas && celdaPosible.columna >= 0)) && (buscarCelda(visitada, celdaPosible) == 0)) {
        if (nuevoL.camino[celdaPosible.renglon][celdaPosible.columna] == 0) {
            return celdaPosible;
        }
    }

    // Abajo.
    celdaPosible.renglon = (celdaActual.renglon) + 1;
    celdaPosible.columna = celdaActual.columna;
    if (((celdaPosible.renglon < nuevoL.renglones && celdaPosible.renglon >= 0) && (celdaPosible.columna < nuevoL.columnas && celdaPosible.columna >= 0)) && (buscarCelda(visitada, celdaPosible) == 0)) {
        if (nuevoL.camino[celdaPosible.renglon][celdaPosible.columna] == 0) {
            return celdaPosible;
        }
    }

    // Arriba.
    celdaPosible.renglon = (celdaActual.renglon) - 1;
    celdaPosible.columna = celdaActual.columna;
    if (((celdaPosible.renglon < nuevoL.renglones && celdaPosible.renglon >= 0) && (celdaPosible.columna < nuevoL.columnas && celdaPosible.columna >= 0)) && (buscarCelda(visitada, celdaPosible) == 0)) {
        if (nuevoL.camino[celdaPosible.renglon][celdaPosible.columna] == 0) {
            return celdaPosible;
        }
    }

    // Izquierda.
    celdaPosible.renglon = celdaActual.renglon;
    celdaPosible.columna = (celdaActual.columna) - 1;
    if (((celdaPosible.renglon < nuevoL.renglones && celdaPosible.renglon >= 0) && (celdaPosible.columna < nuevoL.columnas && celdaPosible.columna >= 0)) && (buscarCelda(visitada, celdaPosible) == 0)) {
        if (nuevoL.camino[celdaPosible.renglon][celdaPosible.columna] == 0) {
            return celdaPosible;
        }
    }

    celdaPosible.renglon = -1; // Si no existe ninguna celda.
    celdaPosible.columna = -1;
    return celdaPosible;
}

// Recorrer la pila en busca de una coordenada.
int buscarCelda(pilaD* visitada, coord celdaActual) {
    int i;
    for (i = 0; i < visitada->nElementos; i++) {
        if (celdaActual.renglon == visitada->elementos[i].renglon && celdaActual.columna == visitada->elementos[i].columna)
            return 1;
    }
    return 0;
    // Return 1 = Ya visitada(se encontro registro) - 0 = NO Visitada (no esta registrada) 
}

// Metodo Backtracking.
void resolverL(laberinto nuevoL, int pasos) {
    int i;
    pilaD resolucion; // Pila que almacena la solucion de los caminos.
    pilaD visitadas; // Pila que mantiene un registro de las celdas visitadas.
    pilaD salidasE; // Pila que mantiene un registro de las salidas encontradas.
    resolucion = arregloDin();
    visitadas = arregloDin();
    salidasE = arregloDin();
    printf("\nIniciando proceso de busqueda de caminos\n");
    arrPush(&resolucion, nuevoL.inicio);
    while (resolucion.nElementos != 0) { // Realizar mientras se llegue al mismo punto de salida o se llegue al numero de posibles salidas.
        coord celdaActual;
        celdaActual = resolucion.elementos[resolucion.nElementos - 1]; // Tope de la pila.
        arrPush(&visitadas, celdaActual);
        if (celdaActual.renglon == 0 || celdaActual.columna == 0 || celdaActual.renglon == (nuevoL.renglones) - 1 || celdaActual.columna == (nuevoL.columnas) - 1) {
            if (celdaActual.renglon != nuevoL.inicio.renglon || celdaActual.columna != nuevoL.inicio.columna) { // No registrar la salida si se trata del inicio.
                if (buscarCelda(&salidasE, celdaActual) == 0) { // Que la salida no este repetida.
                    // Si se recorre la pila resolucion obtenemos los caminos, falta guardar la pila en un archivo
                    printf("\nSe encontro un camino para la salida %d, %d !!\n", celdaActual.columna, celdaActual.renglon);
                    arrPush(&salidasE, celdaActual);
                    if (nuevoL.nSalidas == salidasE.nElementos)
                        break;
                }
            }
        }
        // Buscar opcion de camino.
        if (posibleCelda(nuevoL, celdaActual, &visitadas).renglon != -1 || posibleCelda(nuevoL, celdaActual, &visitadas).columna != -1) {
            if (posibleCelda(nuevoL, celdaActual, &visitadas).renglon == nuevoL.inicio.renglon && posibleCelda(nuevoL, celdaActual, &visitadas).columna == nuevoL.inicio.columna) {
                arrPop(&resolucion);
            }
            arrPush(&resolucion, posibleCelda(nuevoL, celdaActual, &visitadas));
        } else {
            // Paso hacia atras...
            arrPop(&resolucion); // Eliminar movimiento de la pila.
        }
    }
    printf("Se termino el proceso de busqueda.\n");
    if (resolucion.nElementos == 0 && visitadas.nElementos > 0 && salidasE.nElementos == 0) { // En caso de que no existe ningun camino posible.
        printf("No existe ningun camino para alguna de las posibles salidas.");
        arrFree(&visitadas);
    } else {
        arrFree(&visitadas); // Liberar memoria.
        arrFree(&salidasE); // Liberar memoria.
    }

}
/* Fin Laberinto */
