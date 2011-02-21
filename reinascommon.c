/*
 * Archivo: reinascommon.c
 * Código en común para ambas versiones de reinas.
 * Desarrollado por: Victor De Ponte
 *                   Isaac Lopez
 */
#include "reinascommon.h"

#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define FALSE 0
#define TRUE 1
#define TAMAX 10
#endif

#ifndef USEPROC
#define USEPROC
#include <unistd.h>
#endif

#ifndef USETIME
#define USETIME
#include <time.h>
#endif

#ifndef LIMITS
#define LIMITS
#include <limits.h>
#endif


/*INICIO Funciones y Procedimientos referentes al tipo Trie*/

NodeTrie *newNodeTrie(int nChildren, NodeTrie *dad) {
  NodeTrie *nuevo;
  if (nuevo = (NodeTrie *) malloc(sizeof(NodeTrie))){
    nuevo->isWord = nuevo->wordSize = nuevo->numChildren = FALSE;
    nuevo->meta = NULL;
    nuevo->parent = dad;
    if (dad) {
      dad->numChildren++;
    }
    nuevo->children = (NodeTrie **) malloc(nChildren * sizeof(NodeTrie *));
    register int i;
    for (i = 0; i < nChildren; i++) {
      nuevo->children[i] = NULL;
    }
    return nuevo;
  } else {
    perror("Problema reservando memoria para un nuevo NodeTrie!");
    exit(1);
  }
}

Trie *newTrie(int nChildren) {
  Trie *nuevo;
  if (nuevo= (Trie *) malloc( sizeof(Trie))) {
    nuevo->size = 0;
    nuevo->maxChildren = nChildren;
    nuevo->root = newNodeTrie(nChildren,NULL);
    return nuevo;
  } else {
    perror("Problema reservando memoria para un nuevo Trie!");
    exit(1);
  }
}

int nt_free(int nChildren, NodeTrie *node) {
  register int i;
  for (i = 0; i < nChildren; i++) {
    if (node->children[i]) {
      nt_free(nChildren, node->children[i]);
    }
  }
  node->parent = NULL;
  free(node);
  node = NULL;
  return 0;
}

int t_free(Trie *tree){
  if (tree) {
    if (tree->root){
      nt_free(tree->maxChildren ,tree->root);
    }
  }
  tree->root = NULL; 
  free(tree);
  tree = NULL;
  return 0;
}

int T_insert(Trie *tree, int elem[], int tam, double t){
  if (tree) {
    NodeTrie *inUse = tree->root;
    register int i;
    for (i = 0; i < (tam - 1) ; i++) {
       if (inUse->children[elem[i]] == NULL) {
	inUse->children[elem[i]] = newNodeTrie(tree->maxChildren, inUse);
      }
      inUse = inUse->children[elem[i]];
    }
    if (inUse->children[elem[i]] == NULL) {
      inUse->children[elem[i]] = newNodeTrie(tree->maxChildren, inUse);
    }
    inUse = inUse->children[elem[i]];
    inUse->isWord = TRUE;
    inUse->wordSize = tam;
    if (inUse->meta == NULL) {
      inUse->meta = (MetaData *) malloc(sizeof(MetaData));
      inUse->meta->multiplicity = 0;
      inUse->meta->time = INT_MAX;
    }
    inUse->meta->haySolucion = TRUE;
    inUse->meta->multiplicity++;    
    if (t < inUse->meta->time) {
      inUse->meta->time = t;
    }

    tree->size++;
    return 0;
  } else {
    printf("Problema al insertar en un Trie: El Trie no está inicializado!");
    exit(1);
  }
}

void traversal(Trie *respuestas){
  int max = respuestas->maxChildren;
  int *sol = (int *) malloc(max * sizeof(int));
  int posi = 0;
  int nSol = 0;
  int size = respuestas->size;
  printf("Nro. Total de soluciones diferentes: %d",size);
  NodeTrie *inUse = respuestas->root;
  transAux(inUse,0,max,&sol,&posi,&nSol);
}

void transAux(NodeTrie *node, int indice, int max, int **sol, int *posi, int *nSol){
  register int i;
  for (i = 0; i < max; i++) {
    if (node->children[i]) {
      if (0 <= *posi && *posi < max) {
	*sol[*posi] = i;
	*posi++;
      }
      transAux(node->children[i],i,max,sol,posi,nSol);
      *posi--;
    }
    if (node->isWord) {
      *sol[7] = indice;
      printf("   Solucion %d: (0,%d) (1,%d) (2,%d) (3,%d) (4,%d) (5,%d) (6,%d) (7,%d)\n",nSol,sol[0],sol[1],sol[2],sol[3],sol[4],sol[5],sol[6],sol[7]);
      printf("      Tiempo minimo: %d mseg.\n", node->meta->time);
      printf("Nro. de veces encontrada: %d", node->meta->multiplicity);
      *nSol++;
    }
  }
}
/*FIN Funciones y Procedimientos referentes al tipo Trie*/

/*----------------------------------------------------------------------------*/

/*INICIO Funciones y procedimientos referentes al manejo de parámetros*/
void procesarNJobs(char *argv, int *nJobs, char *usage){
  *nJobs = atoi(argv);
  if (*nJobs <= 0) {
    int opt;
    printf("Debe haber al menos un trabajador!");
    printf(usage);
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

void procesarFlagPrint(char *argv, int *flagPrint, char *usage){
  *flagPrint = atoi(argv);
  if (*flagPrint < 0 || 1 < *flagPrint) {
    int opt;
    printf("Los posibles valores para la opción de impresión son cero(0) o uno (1)!\n");
    printf(usage);
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

void procesarArgumentos(int argc, char **argv, int *nJobs, int *flagPrint, char *usage) {
  if (argc != 1) {
    switch (argc)
      {
      case 3:
	if (strcmp(argv[1],"-n") == 0){
	  procesarNJobs(argv[2],nJobs,usage);
	} else if (strcmp(argv[1],"-i") == 0) {
	  procesarFlagPrint(argv[2],flagPrint,usage);
	} else {
	  printf(usage);
	  exit(1);
	}
	break;
      case 5:
	if (strcmp(argv[1],"-n") == 0){
	  if (strcmp(argv[3],"-i") == 0) {
	    procesarNJobs(argv[2],nJobs,usage);
	    procesarFlagPrint(argv[4],flagPrint,usage);
	  } else {
	    printf(usage);
	    exit(1);
	  }
	} else if (strcmp(argv[1],"-i") == 0) {
	  if (strcmp(argv[3],"-n") == 0) {
	    procesarNJobs(argv[4],nJobs,usage);
	    procesarFlagPrint(argv[2],flagPrint,usage);
	  } else {
	    printf(usage);
	    exit(1);
	  }
	} else {
	  printf(usage);
	  exit(1);
	}
	break;
      default:
	printf(usage);
	exit(1);
      }
  }
}

/*FIN Funciones y procedimientos referentes al manejo de parámetros*/

/*----------------------------------------------------------------------------*/
/*FIN DEL ARCHIVO (EOF)*/
