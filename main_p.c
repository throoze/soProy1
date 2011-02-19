/* Archivo: main_p.c
 * Proceso maestro.
 * Autores: Victor De Ponte
 *          Isaac Lopez
 */
#include "main_p.h"


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

#define USO "\nreinas_t: Resuelve el problema de las 8 reinas usando hilos POSIX.\n\nDesarrollado por:\n\tVictor De Ponte, Carnet 05-38087\n\tIsaac Lopez, Carnet 07-41120\n\nUSO:\n\n\tSintaxis:\n\n\t\treinas_t [-n <num_trabajadores>] [-i {1|0}]\n\n\tOpciones:\n\n\t\t-n\tNumero de hilos a resolver el problema. El valor por\n\t\t\tdefecto es 8.\n\t\t-i\tOpcion de impresión. Debe ir seguido de un 1 si se desea\n\t\t\tque cada hilo imprima su resultado, o 0 en caso contra-\n\t\t\trio. El valor por defecto es 0.\n\n"

void job(){

}

void procesarNJobs(char *argv, int *nJobs){
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

void procesarFlagPrint(char *argv, int *flagPrint){
  *flagPrint = atoi(argv);
  if (*flagPrint < 0 || 1 < *flagPrint) {
    int opt;
    printf("Los posibles valores para la opción de impresión son cero(0) o uno (1)!\n");
    printf(USO);
    do {
      printf("\nQue desea hacer???\n");
      printf("\t1) Volver a introducir la opción de impresión.\n");
      printf("\t2) Usar el valor por defecto (0, no imprimir).\n");
      printf("\t3) Abandonar el programa.\n");
      printf("\n\tIntroduzca el numero de opción:\n\t\t>> ");
      scanf("%d",&opt);
    } while (1 > opt || opt >= 4);
    switch (opt)
      {
      case 1:
	do {
	  printf("Por favor intruduzca un valor válido de opción de impresión:\n\t>> ");
	  scanf("%d",flagPrint);
	} while (*flagPrint != 0 || *flagPrint != 1);
	break;
      case 2:
	*flagPrint = 0;
	break;
      case 3:
	printf("Saliendo del programa...\n");
	exit(0);
      }
  }
}

void procesarArgumentos(int argc, char **argv, int *nJobs, int *flagPrint) {
  if (argc != 1) {
    switch (argc)
      {
      case 3:
	if (strcmp(argv[1],"-n") == 0){
	  procesarNJobs(argv[2],nJobs);
	} else if (strcmp(argv[1],"-i") == 0) {
	  procesarFlagPrint(argv[2],flagPrint);
	} else {
	  printf(USO);
	  exit(1);
	}
	break;
      case 5:
	if (strcmp(argv[1],"-n") == 0){
	  if (strcmp(argv[3],"-i") == 0) {
	    procesarNJobs(argv[2],nJobs);
	    procesarFlagPrint(argv[4],flagPrint);
	  } else {
	    printf(USO);
	    exit(1);
	  }
	} else if (strcmp(argv[1],"-i") == 0) {
	  if (strcmp(argv[3],"-n") == 0) {
	    procesarNJobs(argv[4],nJobs);
	    procesarFlagPrint(argv[2],flagPrint);
	  } else {
	    printf(USO);
	    exit(1);
	  }
	} else {
	  printf(USO);
	  exit(1);
	}
	break;
      default:
	printf(USO);
	exit(1);
      }
  }
}

void main(int argc, char **argv){
  int nJobs = 8;
  int flagPrint = 0;
	int espera;
//  printf("argc == %d\n\n", argc);
  
  procesarArgumentos(argc, argv, &nJobs, &flagPrint);
  
//  printf("nJobs: %d, flagPrint: %d\n\n", nJobs, flagPrint);

	pid_t crea;
	if((crea = fork()) == 0){
		execl("/bin/mkdir", "mkdir", "./salidas", NULL);
	}
	wait(&espera);

	pid_t trabajadores[nJobs];
	int h;
	for (h = 0; h < nJobs; h++){
		if ((trabajadores[h]=fork())==0){
			char* argumento1 = malloc(sizeof(char*));
			sprintf(argumento1, "%d",h%8);
			char* argumento2 = malloc(sizeof(char*));
			sprintf(argumento2, "%d",h/8);
			char* argumento3 = malloc(sizeof(char*));
			sprintf(argumento3, "%d",flagPrint);
			execl("./reinas", "./reinas", argumento1, argumento2, argumento3, NULL);
		}
	}
	
	for (h = 0; h < nJobs; h++){
		wait(&espera);
	}
	
	execl("/bin/rm", "rm -r", "-r", "./salidas", NULL);
	
}
