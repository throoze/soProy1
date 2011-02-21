/* Archivo: main_t.h
 * Proceso maestro, Version de hilos.
 * Autores: Victor De Ponte
 *          Isaac Lopez
 */

#ifndef STD
#define STD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0
#define TAMAX 10
#endif

#ifndef ALM
#define ALM
#include "almacenamiento.h"
#endif

#ifndef USETHREADS
#define USETHREADS
#include <pthread.h>
#endif


#ifndef COMMON
#define COMMON
#include "reinascommon.h"
#endif



#ifndef USO
#define USO "\nreinas_t: Resuelve el problema de las 8 reinas usando hilos POSIX.\n\nDesarrollado por:\n\tVictor De Ponte, Carnet 05-38087\n\tIsaac Lopez, Carnet 07-41120\n\nUSO:\n\n\tSintaxis:\n\n\t\treinas_t [-n <num_trabajadores>] [-i {1|0}]\n\n\tOpciones:\n\n\t\t-n\tNumero de hilos a resolver el problema. El valor por\n\t\t\tdefecto es 8.\n\t\t-i\tOpcion de impresión. Debe ir seguido de un 1 si se desea\n\t\t\tque cada hilo imprima su resultado, o 0 en caso contra-\n\t\t\trio. El valor por defecto es 0.\n\n"
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
int rjreal;
int imprime;
int tiempo;
struct timeval start, end;



int rjreal;

struct timeval start;
struct timeval end;

typedef struct args {
  int x;
  int y;
  int imprime;
  Trie *tree;
} Args;
