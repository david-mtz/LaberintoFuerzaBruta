#include <stdio.h>
#include <stdlib.h>
#include "laberinto.h"
/* laberinto.h -> contenido para resolver el laberinto */

/* Recibir argumentos */
int main(int argc, char const *argv[]) {
    if (argc < 4 || argc > 4) { // 4 Argumentos [archivo_actual Laberintos/NombreDelLaberinto.txt x y]
        printf("Introduce los parametros necesarios.\n");
        printf("Ej.: laberinto.txt 1 1\n");
        printf("Primer numero es la coordenada  en x (columna) y segundo numero, coordenada en y (renglon).\n");
        exit(EXIT_FAILURE);
    }

    /* Funciones para trabajar con el laberinto... */
    
    return 0;
}
