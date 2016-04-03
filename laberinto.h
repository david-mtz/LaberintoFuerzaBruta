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

/* Arreglo dinamico, comportamiento como pila. */
// Funcion que inicializa un arreglo dinamico y devuelve una estructura del mismo.
pilaD arregloDin();
// Funcion que agrega un elemento al final del arreglo dinamico.
void arrPush(pilaD* arrD, coord equisye);
// Funcion que elimina el ultimo elemento del arreglo dinamico.
void arrPop(pilaD* arrD);
// Funcion que libera el arreglo dinamico.
void arrFree(pilaD* arrD);
/* Fin arreglo dinamico. */

/* Laberinto */
// Funcion para generar la estructura del laberinto.
laberinto genLab(char const *nombreArc, int iRenglon, int iColumna);
// Funcion que muestra el laberinto.
void imprimirL(laberinto nuevoL);
// Funcion que libera las estructuras y datos del laberinto.
void freeL(laberinto freeL);


#endif

