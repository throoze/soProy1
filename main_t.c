/* Archivo: main_t.c
 * Proceso maestro, Version de hilos.
 * Autores: Victor De Ponte
 *          Isaac Lopez
 */

#include "main_t.h"

#ifndef STD
#define STD
#include <stdio.h>
#include <stdlib.h>
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

#define USO "\nreinas_t: Resuelve el problema de las 8 reinas usando hilos POSIX.\n\nDesarrollado por:\n\tVictor De Ponte, Carnet 05-38087\n\tIsaac Lopez, Carnet 07-XXXXX\n\nUSO:\n\n\tSintaxis:\n\n\t\treinas_t [-n <num_trabajadores>] [-i {1|0}]\n\n\tOpciones:\n\n\t\t-n\tNumero de hilos a resolver el problema. El valor por\n\t\t\tdefecto es 8.\n\t\t-i\tOpcion de impresión. Debe ir seguido de un 1 si se desea\n\t\t\tque cada hilo imprima su resultado, o 0 en caso contra-\n\t\t\trio. El valor por defecto es 0.\n\n"

void job(){

}

void procesarNJobs(int argc, int *argv, int *nJobs, int *printFlag){
  *nJobs = atoi(argv);
  if (*nJobs <= 0) {
    int opt;
    printf("Debe haber al menos un trabajador!");
    printf(USO);
    do {
      printf("\nQue desea hacer???\n");
      printf("\t1) Introducir un nuevo numero de trabajadores.\n");
      printf("\t2) Usar el valor por defecto (8 trabajadores).\n");
      printf("\t3) Abandonar el programa.\n");
      printf("\n\tIntroduzca el numero de opción:\n\t\t>> ");
      scanf("%d",&opt);
    } while (1 > opt || opt >= 4);
    switch (opt)
      {
      case 1:
	do {
	  printf("Por favor intruduzca un numero válido de trabajadores:\n\t>> ");
	  scanf("%d",nJobs);
	} while (*nJobs < 1);
	break;
      case 2:
	*nJobs = 8;
	break;
      case 3:
	printf("Saliendo del programa...\n");
	exit(0);
      }
  }
}

void procesarArgumentos(int argc, int **argv, int *nJobs, int *printFlag) {
  if (argc == 1) {
    *nJobs = 8;
    *printFlag = FALSE;    
  } else {
    switch (argc)
      {
      case 3:
	if (strcmp(argv[1],"-n") == 0){
	  procesarNJobs(argc,argv[2],nJobs,printFlag);
	} else if (strcmp(argv[1],"-i") == 0) {
	} else {
	  printf(USO);
	  exit(1);
	}
	break;
      case 5:
	break;
      default:
	printf(USO);
	exit(1);
      }
  }
}

void main(int argc, char **argv){
  int nJobs;
  int printFlag;
  printf("argc == %d\n\n", argc);
  
  procesarArgumentos(argc, argv, &nJobs, &printFlag);
  
  printf("nJobs: %d, printFlag: %d\n\n", nJobs, printFlag);
}
