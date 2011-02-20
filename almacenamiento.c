/*
 * Archivo: almacenamiento.c
 * Desarrollado por: Victor De Ponte
 *                   Isaac Lopez
 */

#include "almacenamiento.h"
#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define TAMAX 10
#endif

/*INICIO Funciones y Procedimientos referentes al tipo hashLote*/
Segmento  *newSegmento() {
  Segmento *nuevo = (Segmento *) malloc(sizeof(Segmento));
  if (nuevo == NULL) {
    fprintf(stderr, "newSegmento: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  } else {
    nuevo->ini = 1;
    nuevo->size = 0;
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    register int i;
    for (i = 0 ; i < TAMAX; i++){
      nuevo->trozo[i] = 0;
    }
    return nuevo;
  }
}

HashLote *newHashLote(){
  HashLote *nuevo = (HashLote *) malloc(sizeof(HashLote));
  if (nuevo) {
    nuevo->head = newSegmento();
    nuevo->tail = nuevo->head;
    return nuevo;
  } else {
    fprintf(stderr, "newHashLote: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

int calcRango (int pos) {
  int mod = pos % TAMAX;
  if (mod == 0) {
    return (pos - (TAMAX - 1));
  } else if (mod == 1) {
    return pos;
  } else {
    return pos - ((pos % TAMAX) - 1);
  }
}

int calcPosicion (int pos) {
  int mod = (pos % TAMAX);
  if (mod == 0) {
    return (TAMAX - 1);
  } else {
    return (mod - 1);
  }
}

int insertar (HashLote *lote, int pos, int num) {
  Segmento *inUse = lote->head;
  while (inUse) {
    int fin = inUse->ini + (TAMAX - 1);
    if ( inUse->ini <= pos && pos <= fin ) {
      break;
    } else if  ( fin < pos && inUse->sig == NULL ) {
      Segmento *nuevo = newSegmento();
      nuevo->ini = calcRango(pos);
      inUse->sig = nuevo;
      nuevo->ant = inUse;
      inUse = lote->tail = nuevo;
      nuevo = NULL;
      break;
    } else if (pos < inUse->ini && inUse->ant != NULL) {
      Segmento *nuevo = newSegmento();
      nuevo->ini = calcRango(pos);
      inUse->ant->sig = nuevo;
      nuevo->ant = inUse->ant;
      inUse->ant = nuevo;
      nuevo->sig = inUse;
      inUse = nuevo;
      nuevo = NULL;
      break;
    }
    inUse = inUse->sig;
  }
  int newPos = calcPosicion(pos);
  if (inUse->trozo[newPos] == 0) {
    /* SE TRATA DE UNA INSERCIÓN */
    lote->size++;
    inUse->size++;
  } else {
    if (num == 0) {
      /* SE TRATA DE UNA ELIMINACIÓN */
      lote->size--;
      inUse->size--;
    }
  }
  inUse->trozo[newPos] = num;
  if (inUse->size == 0) {
    /* EL SEGMENTO ESTÁ VACÍO, ES INÚTIL, SE LIBERA */
    seg_liberar(lote,inUse);
  }
  inUse = NULL;
  return 0;
}

int get(HashLote *lote, int pos){
  Segmento *inUse = lote->head;
  while (inUse) {
    int fin = inUse->ini + (TAMAX - 1);
    if ( inUse->ini <= pos && pos <= fin ) {
      int newPos = calcPosicion(pos);
      return inUse->trozo[newPos];
    } else if  ( fin < pos && inUse->sig == NULL ) {
      return 0;
    } else if (pos < inUse->ini && inUse->ant != NULL) {
      return 0;
    }
    inUse = inUse->sig;
  }
}

int contiene(HashLote *lote, int pos){
  Segmento *inUse = lote->head;
  while (inUse) {
    int fin = inUse->ini + (TAMAX - 1);
    if ( inUse->ini <= pos && pos <= fin ) {
      int newPos = calcPosicion(pos);
      if (inUse->trozo[newPos] != 0) {
	return 1;
      } else {
	return 0;
      }
    } else if  ( fin < pos && inUse->sig == NULL ) {
      return 0;
    } else if (pos < inUse->ini && inUse->ant != NULL) {
      return 0;
    }
    inUse = inUse->sig;
  }
}

void hl_print(HashLote lote){
  Segmento *inUse = lote.head;
  printf("|-------|---------------|\n");
  printf("|  pos  |   contenido   |\n");
  printf("|-------|---------------|\n");
  while (inUse) {
    register int i;
    for (i = 0; i < TAMAX; i++){
      if (inUse->trozo[i] != 0) {
	int pos = (inUse->ini + i);
	printf("| %d\t| %d\t\t|\n",pos,inUse->trozo[i]);
      }
    }
    inUse = inUse->sig;
  }
  printf("|_______|_______________|\n");
}

int hl_liberar(HashLote *lote){
  Segmento *inUse = lote->head;
  Segmento *siguiente = inUse->sig;
  while (inUse) {
    seg_liberar(lote,inUse);
    inUse = siguiente;
    if (inUse){
      siguiente = inUse->sig;
    }
  }
  lote->head = lote->tail = NULL;
  return 0;
}

int seg_liberar(HashLote *lote, Segmento *seg){
  Segmento *siguiente = seg->sig;
  Segmento *anterior = seg->ant;
  if (siguiente) {
    siguiente->ant = anterior;
  } else {
    lote->tail = seg->ant;
  }
  if (anterior) {
    anterior->sig = siguiente;
  } else {
    lote->head = seg->sig;
  }
  seg->ant = seg->sig = NULL;
  free(seg);
  seg = NULL;
  return 0;
}

int *hltoArray(HashLote *lote){
  Segmento *inUse = lote->head;
  int *arreglo = (int *) malloc( lote->size * sizeof(int));
  int j = 0;
  while (inUse) {
    register int i;
    for (i = 0; i < TAMAX; i++){
      if (inUse->trozo[i] != 0) {
	arreglo[j] = inUse->trozo[i];
	j++;
      }
    }
    inUse = inUse->sig;
  }
  return arreglo;
}

int *posToArray(HashLote *lote){
  Segmento *inUse = lote->head;
  int *arreglo = (int *) malloc( lote->size * sizeof(int));
  int j = 0;
  while (inUse) {
    register int i;
    for (i = 0; i < TAMAX; i++){
      if (inUse->trozo[i] != 0) {
  	arreglo[j] = i + inUse->ini;
  	j++;
      }
    }
    inUse = inUse->sig;
  }
  return arreglo;
}
/*FIN Funciones y Procedimientos referentes al tipo HashLote*/


/*INICIO Funciones y Procedimientos referentes al tipo ListaInt*/
CajitaInt *newCajitaInt() {
  CajitaInt *nueva = (CajitaInt *) malloc(sizeof(CajitaInt));
  if (nueva != NULL) {
    nueva->sig = nueva->ant = NULL;
    return nueva;
  } else {
    fprintf(stderr, "newCajitaInt: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

ListaInt *newListaInt() {
  ListaInt *nueva = (ListaInt *) malloc(sizeof(ListaInt));
  if (nueva != NULL) {
    nueva->head = nueva->tail = NULL;
    nueva->size = 0;
    return nueva;
  } else {
    fprintf(stderr, "newListaInt: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

int add(ListaInt *list, int elem) {
  CajitaInt *nueva = newCajitaInt();
  nueva->data = elem;
  if (list->head != NULL && list->tail != NULL) {
    list->tail->sig = nueva;
    nueva->ant = list->tail;
    nueva->sig = NULL;
    list->tail = nueva;
  } else {
    list->head = list->tail = nueva;
  }
  list->size++;
  nueva = NULL;
  return 0;
}

void delete(ListaInt *list, int elem){
  CajitaInt *aux = list->head;
  while (aux) {
    if (aux->data == elem) {
      if (list->size == 1) {
	free(aux);
	aux = list->head = list->tail = NULL;
	return;
      }
      if (aux->ant) {
	aux->ant->sig = aux->sig;
      } else {
	list->head = aux->sig;
      }
      if (aux->sig) {
	aux->sig->ant = aux->ant;
      } else {
	list->tail = aux->ant;
      }
      aux->ant = aux->sig = NULL;
      free(aux);
      aux = NULL;
      list->size--;
      return;
    }
    aux = aux->sig;
  }
  return;
}

int isIn(ListaInt *list, int elem){
  CajitaInt *aux = list->head;
  while (aux) {
    if (aux->data == elem) {
      return TRUE;
    }
    aux = aux->sig;
  }
  return FALSE;
}

void li_print(ListaInt lista){
  CajitaInt *aux = lista.head;
  printf("|-------|\n");
  while (aux) {
    printf("|%d\t|\n", aux->data);
    aux = aux->sig;
  }
  printf("|_______|\n");
}

int li_liberar(ListaInt *list){
  CajitaInt *aux = list->head;
  CajitaInt *siguiente;
  while (aux) {
    if (list->size == 1) {
      free(aux);
      aux = list->head = list->tail = NULL;
      return;
    }
    if (aux->ant) {
      aux->ant->sig = aux->sig;
    } else {
      list->head = aux->sig;
    }
    if (aux->sig) {
      aux->sig->ant = aux->ant;
    } else {
      list->tail = aux->ant;
    }
    siguiente = aux->sig;
    aux->ant = aux->sig = NULL;
    free(aux);
    aux = NULL;
    list->size--;
    aux = siguiente;
    siguiente = NULL;
  }
  aux = siguiente = NULL;
  return;
}

/*FIN Funciones y Procedimientos referentes al tipo ListaInt*/

/*INICIO Funciones y Procedimientos referentes al tipo Trie*/
NodeTrie *newNodeTrie(int nChildren, NodeTrie *dad) {
  NodeTrie *nuevo;
  if (nuevo = (NodeTrie *) malloc(sizeof(NodeTrie))){
    nuevo->isWord = nuevo->multiplicity = nuevo->numChildren = FALSE;
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

Trie *newTrie(int nChildren){
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

int nt_free(int nChildren, NodeTrie *node){
  register int i;
  for (i = 0; i < nChildren; i++) {
    if (node->children[i]) {
      nt_free(nChildren, node->children[i]);
    }
  }
  node->parent = node->extraInfo = NULL;
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

int T_insert(Trie *tree, int *elem, void *info){
  int tam = (sizeof(elem)/sizeof(int));
  if (tree) {
    NodeTrie *inUse = tree->root;
    register int i;
    for (i = 0; i < (tam - 1) ; i++) {
      if (inUse->children[elem[i]] == NULL) {
	inUse->children[elem[i]] = newNodeTrie(tree->maxChildren, inUse);
      }
      inUse = inUse->children[elem[i]];
    }
    i++;
    if (inUse->children[elem[i]] == NULL) {
      inUse->children[elem[i]] = newNodeTrie(tree->maxChildren, inUse);
    }
    inUse->extraInfo = info;
    inUse->isWord = TRUE;
    inUse->wordSize = tam;
    inUse->multiplicity++;
    tree->size++;
    return 0;
  } else {
    printf("Problema al insertar en un Trie: El Trie no está inicializado!");
    exit(1);
  }
}

int **extractWords(Trie *tree){
  int treeSize = tree->size;
  int **words = extractAux(tree->root,tree->maxChildren);
  return words;
}

int **extractAux(NodeTrie *node, int max) {
  int **words = (int **) malloc(countWords(node,max) * sizeof(int *));
  int i = 0;
  if (node) {
    if(node->isWord) {
      int *aux = (int *) malloc(sizeof(int));
      aux[0] = -1;
      words[i] = aux;
      aux = NULL;
      i = 1;
    }
    int k;
    for (k = 0; k < max; k++) {
      if (node->children[k]) {
	int **tmp = extractAux(node->children[k],max);
	
	if (tmp) {
	  int tmpTam = (sizeof(tmp)/sizeof(int *));
	
	  register int c;
	  for (c = 0; c < tmpTam; c++) {
	    int tamW = sizeof(tmp[c])/sizeof(int);
	    int empty = (tamW == 1 && tmp[0] == -1 ? TRUE : FALSE);
	    int tamNW = tamW + (empty ? 0 : 1);
	    words[i] = (int *) malloc(tamNW * sizeof(int));
	    words[i][0] = k;
	    if (!empty) {
	      register int j;
	      for (j = 1; j < tamNW; j++){
		words[i][j] = tmp[c][j-1];
	      }
	    }
	    i++;
	  }
	}
	matrix_free(tmp);
      }
    }
  }
  return words;
}

void matrix_free(int **matrix) {
  register int i,j;
  int m = sizeof(matrix)/sizeof(int *);
  for (i = 0; i < m; i++) {
    free(matrix[i]);
    matrix[i] = NULL;
  }
  free(matrix);
  matrix = NULL;
}

int countWords(NodeTrie *node, int max) {
  int n = 0;
  if (node) {
    register int k;
    for (k = 0; k < max; k++) {
      if (node->children[k]) {
	n = n + countWords(node->children[k],max);
      }
    }
    return (n + (node->isWord ? 1 : 0));
  } else {
    return 0;
  }
}

/*FIN Funciones y Procedimientos referentes al tipo Trie*/

/*FIN DEL ARCHIVO (EOF)*/
