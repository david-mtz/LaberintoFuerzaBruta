#include "laberinto.h"
/* SOLO FUNCIONES PARA LEER, GUARDAR, MANIPULAR Y RESOLVER EL LABERINTO */

/* aqui empezaremos a generar el laberinto, recibimos el nombre del archivo, la coordenada x, la coordenada y */
/* Laberinto */

/* Generar laberinto */
laberinto genLab(char const *nombreArc, int iColumna, int iRenglon) {
	int renglones=1, columnas=0; // Conteo de renglones y columnas.
	int i, j, conteo=1; // Conteo -> Si ya se contaron las columnas, ya no seguir contandolas || Conteo para las salidas.
	int s; // Conteo de salidas.
	int c; // Lectura de caracter.
	FILE *archivo;
	laberinto labtmp;

	archivo = fopen(nombreArc, "r");
	if(archivo == NULL){
		printf("Archivo inexistente.\n");
		exit(EXIT_FAILURE);
	}

	c = fgetc(archivo); 
	// Contabilizar columnas y renglones para reservar memoria.
	// c=32 -> espacio en blanco || c=10 & c=13 -> salto de linea
	while(!feof(archivo)){
		if(c != 32 && c != 10 && c != 13 && conteo == 1) // Conteo de caracteres mientras no sean espacios o saltos de linea.
			columnas++;
		if(c == 10){ // Conteo de saltos de linea para saber los renglones,
			renglones++;
			conteo = 0;
		}
		c = fgetc(archivo);
	}

	labtmp.camino = (int**)malloc(renglones*sizeof(int*));
	if(labtmp.camino != NULL){
		for(i=0;i<renglones;i++) {
			labtmp.camino[i] = (int*)malloc(columnas*sizeof(int));
			if(labtmp.camino[i] == NULL) {
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
	while(!feof(archivo)){
		if(c == 10) // Si se dettecta un salto de linea, hay nuevo renglon.
			i++;
		if(c != 32 && c != 10 && c != 13) { // Mientras no sea un salto de linea o un espacio se guarda en el arreglo.
			labtmp.camino[i][j] = (int)c -48; // De char a int.
			if( (i == 0 || j == 0 || i == renglones-1|| j == columnas-1) && ((int)c -48 == 0) ) { // Detectar posibles salidas.
				labtmp.nSalidas += 1;
			}
			j++;
			if(j == columnas)
				j = 0;
		}
		c = fgetc(archivo);

	}
	fclose(archivo);

	if(labtmp.nSalidas == 0) {
		printf("El laberinto no tendra solucion, no exise ninguna salida.\n");
		exit(EXIT_FAILURE);
	}

	labtmp.renglones = renglones; // Renglones (x) del laberinto.
	labtmp.columnas = columnas; // Columnas (y) del laberinto.

	if(iRenglon<0 || iRenglon>=renglones || iColumna <0 || iColumna>=columnas) { // Evitar violacion de segmento.
		printf("La salida no es valida.\n");
		exit(EXIT_FAILURE);
	}

	if(labtmp.camino[iRenglon][iColumna] ==  0) { // Asegurar que se trata de un camino y no una pared.
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
	for(i=0; i<nuevoL.renglones; i++) {
		for (j=0; j<nuevoL.columnas; j++){
			if(nuevoL.camino[i][j] == 0)
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
