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

#ifndef COMMON
#define COMMON
#include "reinascommon.h"
#endif

#ifndef USEPROC
#define USEPROC
#include <unistd.h>
#endif

#ifndef USO
#define USO "\nreinas_p: Resuelve el problema de las 8 reinas usando Procesos hijos.\n\nDesarrollado por:\n\tVictor De Ponte, Carnet 05-38087\n\tIsaac Lopez, Carnet 07-41120\n\nUSO:\n\n\tSintaxis:\n\n\t\treinas_p [-n <num_trabajadores>] [-i {1|0}]\n\n\tOpciones:\n\n\t\t-n\tNumero de hijos a resolver el problema. El valor por\n\t\t\tdefecto es 8.\n\t\t-i\tOpcion de impresión. Debe ir seguido de un 1 si se desea\n\t\t\tque cada hijo imprima su resultado, o 0 en caso contra-\n\t\t\trio. El valor por defecto es 0.\n\n"
#endif

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
