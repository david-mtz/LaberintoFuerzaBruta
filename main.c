#include <stdio.h>
#include <stdlib.h>
#include "laberinto.h"
/* laberinto.h -> contenido para resolver el laberinto */

/* Recibir argumentos */
int main(int argc, char const *argv[]) {
	char pasoxpaso;
	if(argc < 4 || argc >4 ){
		printf("Introduce los parametros necesarios.\n");
		printf("Ej.: laberinto.txt 1 1\n");
		printf("Primer numero, coordenada  en x(columna) y segundo numero, coordenada en y(renglon).\n");
		exit(EXIT_FAILURE);
	}

	laberinto nuevoL;

	nuevoL = genLab(argv[1], atoi(argv[2]), atoi(argv[3]));

	imprimirL(nuevoL);
	
    return 0;
}
