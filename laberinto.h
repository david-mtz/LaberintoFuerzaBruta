#ifndef _LABERINTO_H_
#define _LABERINTO_H_

#include <stdio.h>
#include <stdlib.h>

#define archivoSol "soluciones.txt" // Archivo de salida de las soluciones. (aqui se almacenan las soluciones del laberinto)

/* DECLARACION DE FUNCIONES, ESTRUCTURAS, ETC */
/* ARCHIVO DE INFORMACION DE CADA FUNCION */

#endif

int main() 
{
    int i, j;
    int caracteres=0;  
    int renglones=0;
    int columnas=0;
    int laberinto[renglones][columnas];
	char caracter;      
    FILE *fp;
 
    fp = fopen("ejemplo1.txt","r");
    if(fp==NULL){
	printf("Error no se pudo leer el arhivo");
    }
    
    else{	
    while (feof(fp) == 0)      /* Mientras no se lea el caracter EOF (End Of File) */
            {
                caracter = fgetc(fp);
                if(caracter=='\n' || caracter==EOF ){
                	caracteres=caracteres-1;
                	renglones=renglones+1;
				}
				
                printf("%c",caracter);
                caracteres=caracteres+1;
            }
        
	columnas=caracteres/renglones;
	printf("\n\nSe leyeron en total %d caracteres  %d renglones y %d columnas \n",caracteres,renglones,columnas);
	fclose(fp);
	
	
	printf("Mostrando el archivo pero almacenado en una matriz\n");
	
	fp = fopen("ejemplo1.txt","r");
	
	if(fp==NULL){
	printf("Error no se pudo leer el arhivo");
	}
	
    for(i=0;i<renglones;i++)
    {
        for(j=0;j<columnas;j++)
        {
            fscanf(fp, "%1d", &laberinto[i][j]);     
            printf("%d", laberinto[i][j]);              
        }
        printf("\n");      //cada vez que se termina una fila hay que pasar a la siguiente linea
    }
 
    fclose(fp);
    
	
    return 0;
    
}

}
