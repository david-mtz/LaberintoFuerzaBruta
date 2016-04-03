#include <stdio.h>
#include <stdlib.h>
#include "laberinto.h"

/* Recibir argumentos */
int main(int argc, char const *argv[]) {
    char pasoxpaso;
    if (argc < 4 || argc > 4) { // 4 Argumentos [archivo nom_laberinto x y]
        printf("Introduce los parametros necesarios.\n");
        printf("Ej.: laberinto.txt 1 1\n");
        printf("Primer numero, coordenada  en x(columna) y segundo numero, coordenada en y(renglon).\n");
        exit(EXIT_FAILURE);
    }

    laberinto nuevoL;

    nuevoL = genLab(argv[1], atoi(argv[2]), atoi(argv[3])); // Generar laberinto.

    imprimirL(nuevoL); // Imprimir el laberinto.

    printf("Deseas que se muestre paso a paso la resolucion? S = Si\n"); // Activar la funcion simularPaso.
    pasoxpaso = getchar();

    if (pasoxpaso == 's' || pasoxpaso == 'S')
        resolverL(nuevoL, 1); // Activa la funcion simularPaso.
    else
        resolverL(nuevoL, 0); // Modo normal, sin mostrar proceso paso a paso.

    freeL(nuevoL);
    return 0;
}
