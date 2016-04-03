#ifndef _LABERINTO_H_
#define _LABERINTO_H_

#include <stdio.h>
#include <stdlib.h>

#define archivoSol "soluciones.txt" // Archivo de salida de las soluciones. (aqui se almacenan las soluciones del laberinto)

// Estructura que identifica las coordenadas.
typedef struct coordenadas {
	int renglon; // Posicion en renglon (eje y)
	int columna; // Posicion en columna (eje x)
} coord;

// Estructura principal, especifica para el laberinto.
typedef struct structLab {
	int **camino; // Almacenar el camino del laberinto.
	int columnas; // # de columnas.
	int renglones; // # de renglones.
	int nSalidas; // # de salidas posibles.
	coord inicio; // Coordenadas de inicio.

} laberinto;

#endif

