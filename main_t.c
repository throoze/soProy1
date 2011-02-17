/* Archivo: main_t.c
 * Proceso maestro, Version de hilos.
 * Autores: Victor De Ponte
 *          Isaac Lopez
 */

#include "main_t.h"

#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
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

/* #define USO "reinas_t: Resuelve el problema de las 8 reinas usando hilos POSIX.\nDesarrollado por:\n\tVictor De Ponte, Carnet 05-38087\n\tIsaac Lopez, Carnet 07-XXXXX\n\nUSO:\n\n\t\treinas_t [-n <num_trabajadores>] [-i {1|0}]\n\nOpciones:\n\t-n\t\tNumero de hilos a resolver el problema. El valor por defecto es 8.\n\t-i\t\tOpcion de impresión. Debe ir seguido de un 1 si se desea que cada hilo imprima su resultado, o 0 en caso contrario. El valor por defecto es 0.\n\n" */

void job(){

}

void main(int argc, char argv[]){
  int nJobs;
  int printFlag;
  if (argc == 1) {
    nJobs = 8;
    printFlag = FALSE;
  } else if (argc > 5) {
    
  }
  
  printf("nJobs: %d, printFlag: %d\n\n", nJobs, printFlag);
}
