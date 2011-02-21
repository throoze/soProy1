/*
 * Archivo: reinascommon.h
 * Código en común para ambas versiones de reinas.
 * HEADER
 * Desarrollado por: Victor De Ponte
 *                   Isaac Lopez
 */

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

/*INICIO declaración del tipo Trie*/

typedef struct meta MetaData;

struct meta {
  int haySolucion;
  int multiplicity;
  double time;
};

typedef struct nodeTrie NodeTrie;

struct nodeTrie {
  int isWord;
  int wordSize;
  int numChildren;
  MetaData *meta;
  NodeTrie *parent;
  NodeTrie **children;
};

typedef struct {
  NodeTrie *root;
  int size;
  int maxChildren;
} Trie;
/*FIN declaración del tipo Trie*/

/*INICIO Funciones y procedimientos referentes al tipo Trie*/
/**
 * Crea un nuevo NodeTrie, reservando la memoria necesaria para ello.
 * nChildren: Número máximo de hijos que podrá tener un NodeTrie.
 * retorna: Un apuntador a un nuevo NodeTrie vacío.
 */
NodeTrie *newNodeTrie(int nChildren, NodeTrie *dad);

/**
 * Crea un nuevo Trie, reservando la memoria necesaria para ello.
 * nChildren: Número máximo de hijos que podrá tener un nodo de este Trie.
 * retorna: Un apuntador a un nuevo Trie vacío.
 */
Trie *newTrie(int nChildren);

/**
 * Se encarga de liberar recursivamente la memoria ocupada por un NodeTrie.
 * nChildren: numero Máximo de hijos que tiene el NodeTrie a liberar.
 * node: apuntador al NodeTrie a liberar.
 * retorna: 0 si la liberación tuvo éxito; en caso contrario, retorna un error.
 */
int nt_free(int nChildren, NodeTrie *node);

/**
 * Se encarga de liberar la memoria ocupada por un Trie.
 * tree: Trie a liberar.
 * retorna: 0 si la liberación tuvo éxito; en caso contrario, retorna un error.
 */
int t_free(Trie *tree);

/**
 * Inserta el elemento 'elem' en el Trie 'tree'.
 * tree: Apuntador al Trie donde se insertará el elemento 'elem'.
 * elem: Elemento a insertar, Es un arreglo de enteros que representan las
 *       "letras" de la "palabra" que se inserta.
 * t: tiempo de la respuesta encontrada.
 * auth: autor de la respuesta dada.
 * retorna: 0 si la inserción tuvo éxito, 1 en caso contrario.
 */
int T_insert(Trie *tree, int elem[], int tam, double t);

/**
 * Se encarga de comenzar la recursion que recorrera el Trie y escribirá el 
 * resumen de las soluciones obtenidas.
 * respuestas: Apuntador al Trie que contiene las respuestas obtenidas.
 */
void traversal(Trie *respuestas);

/**
 * Función auxiliar que recorre el Trie recursivamente en busca de las respues-
 * tas almacenadas en él.
 * node: NodeTrie donde se empezará la búsqueda recursiva.
 * indice: Identificador del NodeTrie que fue llamado en la recursión anterior.
 * max: Maximo de NodeTrie's hijos que puede tener un NodeTrie en este Arbol.
 * sol: Arreglo que guardará la solucion que se esta leyendo.
 * posi: Indice de la posicion que se esta usando el arreglo 'sol'.
 * nSol: Número de solución que se esta leyendo.
 */
void transAux(NodeTrie *node, int indice, int max, int sol[], int *posi, int *nSol);

/*FIN Funciones y procedimientos referentes al tipo Trie*/

/*----------------------------------------------------------------------------*/

/*INICIO Funciones y procedimientos referentes al manejo de parámetros*/
/**
 * Se encarga de procesar el parámetro -n en caso de ser encontrado en la en-
 * trada.
 * argv: valor del parámetro correspondiente a -n.
 * nJobs: variable que almacenará el valor de argv luego de que este sea pro-
 *        cesado.
 * usage: Cadena que contiene instrucciones de uso del programa.
 */
void procesarNJobs(char *argv, int *nJobs, char *usage);

/**
 * Se encarga de procesar el parámetro -i en caso de ser encontrado en la en-
 * trada.
 * argv: valor del parámetro correspondiente a -i.
 * flagPrint: variable que almacenará el valor de argv luego de que este sea 
 *            procesado.
 * usage: Cadena que contiene instrucciones de uso del programa.
 */
void procesarFlagPrint(char *argv, int *flagPrint, char *usage);

/**
 * Se encarga de coordinar el procesamiento de los argumentos de entrada.
 * argc: numero de parámetros pasados al programa.
 * argv: arreglo de cadenas de caracteres que contiene todos los parámetros
 *       pasados como argumentos al programa.
 * nJobs: variable que almacenará el valor de argv luego de que este sea pro-
 *        cesado.
 * flagPrint: variable que almacenará el valor de argv luego de que este sea 
 *            procesado.
 * usage: Cadena que contiene instrucciones de uso del programa.
 */
void procesarArgumentos(int argc, char **argv, int *nJobs, int *flagPrint, char *usage);
/*FIN Funciones y procedimientos referentes al manejo de parámetros*/

/*----------------------------------------------------------------------------*/
/*FIN DEL ARCHIVO (EOF)*/
