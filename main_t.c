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

#ifndef COMMON
#define COMMON
#include "reinascommon.h"
#endif

#ifndef USETHREADS
#define USETHREADS
#include <pthread.h>
#endif

#ifndef USO
#define USO "\nreinas_t: Resuelve el problema de las 8 reinas usando hilos POSIX.\n\nDesarrollado por:\n\tVictor De Ponte, Carnet 05-38087\n\tIsaac Lopez, Carnet 07-41120\n\nUSO:\n\n\tSintaxis:\n\n\t\treinas_t [-n <num_trabajadores>] [-i {1|0}]\n\n\tOpciones:\n\n\t\t-n\tNumero de hilos a resolver el problema. El valor por\n\t\t\tdefecto es 8.\n\t\t-i\tOpcion de impresión. Debe ir seguido de un 1 si se desea\n\t\t\tque cada hilo imprima su resultado, o 0 en caso contra-\n\t\t\trio. El valor por defecto es 0.\n\n"
#endif

// ############# calculo reinas ####################

void try(int i, Trie *tree){
  int j;
  if(i == ri && i != 7) i++;
  for (j = 0; j < 8; j++){

    if ((a[j] && b[i+j] && c[i-j+7]) || (i == 7 && ri == i)){
      if (ri != i){      
	x[i]=j;
	a[j]=FALSE;
	b[i+j]=FALSE;
	c[i-j+7]=FALSE;
      }
      if (i < 7) try(i+1,tree);
      else{
	gettimeofday(&end, NULL);
	int tiempo = ((end.tv_sec * 1000000 + end.tv_usec)
		      - (start.tv_sec * 1000000 + start.tv_usec));
	int k;
	if (imprime){
	  char *resultado = malloc(200);
	  sprintf(resultado, "   Resultado del hijo %d:\n      Solucion: ",ri+(rjreal*8) + 1);
	  for(k = 0 ; k < 8  ; k++) {
	    if(k == 7) {
	      sprintf(resultado, "%s(%d,%d)\n",resultado,k,x[k]);
	    }
	    else {
	      sprintf(resultado, "%s(%d,%d) ",resultado,k,x[k]);
	    }
	  }
	  sprintf(resultado, "%s          Tiempo (milisegundos): %d\n",resultado, tiempo);
	  sprintf(resultado, "%s          Tablero inicial: (%d,%d)\n\n",resultado,  ri, rj);
	  printf(resultado);
	  
	}
	T_insert(tree,x,8,tiempo);
	//	  printf("salgo\n");
	  pthread_exit(NULL);	 	
	

      }	
      a[j]=TRUE;
      b[i+j]=TRUE;
      c[i-j+7]=TRUE;	
    }      
  }
}
void *reinas(void *argumentos){
  Args *arg = (Args *) argumentos;
  ri = arg->x;
  rj = arg->y % 8;
  rjreal = arg->y;
  imprime = arg->imprime;
  //  printf("entrada = (%d,%d,%d)\n",ri,rj,imprime);
  int fin = 1;

  int i;
  for(i = 0; i < 8; i++){ 
    a[i] = TRUE;
  }
  for(i = 0; i < 15; i++){ 
    b[i] = TRUE;
  } 
  for(i = 0; i < 15; i++){ 
    c[i] = TRUE;
  }
  
  x[ri] = rj;
  a[rj] = FALSE;
  b[ri + rj] = FALSE;
  c[ri - rj + 7] = FALSE;

  gettimeofday(&start, NULL);
  try(0, arg->tree);
   
  return;
}


//################## main #######################


void main(int argc, char **argv){
  int nJobs = 8;
  int flagPrint = 0;
  //  printf("argc == %d\n\n", argc);
  
  procesarArgumentos(argc, argv, &nJobs, &flagPrint, USO);
  
  //printf("nJobs: %d, flagPrint: %d\n\n", nJobs, flagPrint);


  pthread_t tid[nJobs];
  int h;
  int estado;
  Trie *answers = newTrie(8);
  Args *argumentos = (Args *) malloc(sizeof(Args));
  argumentos->tree = answers;

  for (h = 0; h < nJobs; h++){
    argumentos->x = h%8;
    argumentos->y = h/8; 
    argumentos->imprime = flagPrint;
    printf("Todo fino: %d\n",h);
    fflush(stdout);
    if (pthread_create(&tid[h],NULL,reinas, (void *)argumentos)){
           perror("ERROR AL CREAR EL HIJO");
    }
    else{
      //      printf("hijo creados\n");
    }
  }
  for (h = 0; h < nJobs; h++) {
    //  printf("hola1\n");
    fflush(stdout);
    //   pthread_join(tid[h], NULL);
    //   printf("hola2\n");
    fflush(stdout); 
 }
  //  printf("hola3\n");
    fflush(stdout);
    traversal(answers);
    pthread_exit(NULL);	 	
}
