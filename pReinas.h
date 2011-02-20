/*
 * Archivo: pReinas.h
 * Código del algoritmo que encuentra las soluciones.
 * HEADER
 * Desarrollado por: Victor De Ponte
 *                   Isaac Lopez
 */

#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#endif


#ifndef USEPROC
#define USEPROC
#include <unistd.h>
#endif

#ifndef USETIME
#define USETIME
#include <time.h>
#endif


int a[8]; // a[i]=TRUE indica que no hay una reina en la i-ésima columna

int b[15]; // b[i]=TRUE indica que no hay una reina en la i-ésima
// diagonal que va desde el extremo superior derecho
// hacia el inferior izquierdo

int c[15]; // c[i]=TRUE indica que no hay una reina en la i-ésima
// diagonal que va desde el extremo izquierdo
// superior hacia el inferior derecho

int x[8]; // indica la posición de la reina en la columna i-ésima

int ri;
int rj;
int imprime;
clock_t tiempo;

void try(int i);
