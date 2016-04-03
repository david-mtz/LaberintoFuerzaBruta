#ifndef _LABERINTO_H_
#define _LABERINTO_H_

#include <stdio.h>
#include <stdlib.h>

#define archivoSol "soluciones.txt" // Archivo de salida de las soluciones.

// Algoritmo que resuelve un laberinto, metodo de la mano derecha con backtracking,
// Camino = 0
// Paredes = 1

// Estructura que identifica las coordenadas.
typedef struct coordenadas {
	int renglon; // Posicion en renglon (eje y)
	int columna; // Posicion en columna (eje x)
} coord;

// Estructura para trabajar un arreglo dinamico y que almacena las coordenadas.
typedef struct pilaDin {
	int nElementos; // # de elementos.
	coord *elementos; // Arreglo
} pilaD;

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

/* Escritura de Archivo Solucion */
// Funcion que crea el archivo solucion.
void generarArc();
// Funcion que añade soluciones en el archivo.
void aniadirArc(pilaD* solucion);
/* FIn de Escritura de Archivo Solucion */


/* Laberinto */
// Funcion para generar la estructura del laberinto.
laberinto genLab(char const *nombreArc, int iRenglon, int iColumna);
// Funcion que muestra el laberinto.
void imprimirL(laberinto nuevoL);
// Funcion que libera las estructuras y datos del laberinto.
void freeL(laberinto freeL);
/* Resolucion de laberinto */
// Funcion que devuelve la posible celda para el siguiente movimiento.
coord posibleCelda(laberinto nuevoL, coord celdaActual, pilaD* visitada);
// Funcion que recorre un arreglo dinamico en busca de una coordenada.
int buscarCelda(pilaD* visitada, coord celdaActual);
// Funcion que devuelve el estado del recorrido en el laberinto segun la pila de soluciones.
void simularPaso(laberinto  nuevoL, pilaD* resolucion);
// Funcion que resuelve el laberinto.
void resolverL(laberinto nuevoL, int pasos);
/* Fin Laberinto */
#endif
