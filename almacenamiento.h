#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define TRUE 1
#define FALSE 0
#define TAMAX 10
#endif


/*INICIO definición del tipo HashLote*/
/**
 * Híbrido entre lista y arreglos, basicamente es una lista enlazada de 
 * arreglos, que utilizaremos para almacenar elementos que estén relacionados 
 * con la posición que ocupan, para luego poder ubicarlos facilmente y 
 * agilizar la búsqueda. Una posición se considera ocupada si su contenido es 
 * diferente de cero (0). De ahi que no se haya implementado la función que 
 * elimine el contenido de una posición; basta con insertar el elemento cero (0)
 * en la posición cuyo contenido se desee eliminar.
 * 
 * trozo: Arreglo que guarda lo correspondiente a un rango de tamaño TAMAX y
 *        representa las posiciones compendidas entre 'ini' y ('ini' + TAMAX -1)
 *        inclusive.
 * 
 * ini: Entero que representa el comienzo del rango de este Segmento.
 * 
 * size: Entero que representa cuántas casillas hay ocupadas en este Segmento.
 * 
 * *ant: Apuntador al Segmento anterior.
 * 
 * *sig: Apuntador al siguiente Segmento.
 * 
 */
typedef struct segmento Segmento;

struct segmento {
  int trozo[TAMAX], ini, size;
  Segmento *ant, *sig;
  };

/**
 * Acceso rápido a la cabeza y cola de la lista de Segmentos.
 * 
 * *head: Apuntador al primer Segmento de este HashLote.
 * 
 * *tail: Apuntador al último Segmento de este HashLote.
 * 
 * size: Entero que dice cuántas casillas hay ocupadas.
 */
typedef struct {
  Segmento *head,*tail;
  int size;
} HashLote;
/*FIN del tipo HashLote*/

/*----------------------------------------------------------------------------*/


/*INICIO Funciones y Procedimientos referentes al tipo hashLote*/
/**
 * Constructor del tipo Segmento. Se encarga de hacer la reserva de memoria y de
 * inicializar los campos convenientemente. El contenido del arreglo (trozo) se 
 * inicializa en 0.
 *
 * retorna: un apuntador a Segmento nuevo, inicializado, con su correspondiente 
 * reserva de memoria.
 */
Segmento *newSegmento();

/**
 * Constructor del tipo HashLote. Se encarga de hacer la reserva de memoria.
 * 
 * retorna: un nuevo apuntador a HashLote con su correspondiente reserva de 
 * memoria.
 */
HashLote *newHashLote();

/**
 * Sirve para calcular el Segmento al que corresponde la posicion pasada como 
 * argumento.
 * 
 * pos: posición a la cual se le quiere calcular el rango.
 * 
 * retorna: Entero que indica el inicio del rango al que corresponde 'pos'.
 *          El final del rango es calculable sumando (x + (TAMAX - 1)), donde 
 *          'x' es el número devuelto por esta función.
 */
int calcRango(int pos);

/**funcion a ser utilizada solo si existe un unico elemento en el HashLote
 *que devuelve la posicion del elemento
 */
int unico(HashLote *lote);

/**
 * Calcula la posicion interna dentro de un Segmento donde debe ir 'pos'
 * 
 * pos: posición a la cual se le calcula la posición interna en el trozo de 
 *      HashLote.
 * 
 * retorna: Posición interna en el arreglo del segmento al cual corresponde la 
 *          posición 'pos'.
 */
int calcPosicion(int pos);

/**
 * Inserta el numero 'num' en la posición 'pos' del HashLote '*lote'.
 * 
 * *lote: apuntador al lote donde se desea hacer la inserción.
 * 
 * pos: posición en la que se desea insertar.
 * 
 * num: número a insertar en el HashLote.
 * 
 * retorna: Un entero que indica el estado de la inserción; 0 si fue realizada 
 *          con éxito, cualquier otro número en caso contrario.
 */
int insertar(HashLote *lote, int pos, int num);

/**
 * Devuelve el elemento almacenado en la posición 'pos', en el HashLote 'lote'.
 * 
 * *lote: apuntador al lote donde se buscará el elemento.
 * 
 * pos: posición que se desea buscar  en el HashLote *lote.
 * 
 * retorna: el elemento en el HashLote '*lote' en la posición 'pos', en caso de
 *          estar. Devuelve 0 si el elemento en la posición 'pos' no ha sido 
 *          asignado; y -1 en caso de que el segmento correspondiente a la 
 *          posición buscada no exista.
 */
int get(HashLote *lote, int pos);


/**
 * Dice si el elemento en la posición 'pos' ha sido insertado en el HashLote 
 * '*lote'.
 * *lote: apuntador al lote donde se buscará el elemento.
 * 
 * pos: posición que se desea buscar en el HashLote *lote.
 * 
 * retorna: 1 en caso de que el elemento en la posición 'pos' haya sido asignado;
 *          0 en caso contrario.
 */
int contiene(HashLote *lote, int pos);

/**
 * Imprime en la salida estándar el contenido útil del HashLote 'lote'.
 * 
 * lote: El HashLote que se desea imprimir por la salida estándar.
 */
void hl_print(HashLote lote);

/**
 * Se encarga de devolver un HashLote a su estado original vacío, liberando la
 * memoria consumida por éste. El apuntador Lote queda apuntando a una lista
 * vacía.
 * 
 * lote: Un apuntador al HashLote que se desea limpiar.
 * 
 * retorna: 0 si se completó la limpieza con éxito, 1 en caso contrario.
 */
int hl_liberar(HashLote *lote);

/**
 * Se encarga de devolver un Segmento a su estado original vacío, liberando la
 * memoria consumida por éste.
 * 
 * lote: Un apuntador al Segmento que se desea limpiar.
 * 
 * retorna: 0 si se completó la limpieza con éxito, 1 en caso contrario.
 */
int seg_liberar(HashLote *lote, Segmento *segm);


/**
 * Devuelve un arreglo que contiene todos los elementos del HashLote 'lote'.
 * 
 * lote: El HashLote a transferir a arreglo.
 * 
 */
int *hltoArray(HashLote *lote);

/**
 * Devuelve un arreglo que contiene todas las posiciones ocupadas en
 * el HashLote 'lote' por los elementos almacenados.
 * lote: El HashLote a transferir a arreglo.
 * 
 */
int *posToArray(HashLote *lote);
/*FIN Funciones y Procedimientos referentes al tipo HashLote*/

/*----------------------------------------------------------------------------*/

/*INICIO definición del tipo ListaInt.*/

/**
 * Clasica lista de elementos. Es una lista de apuntadores a void, con lo cual
 * se podra almacenar practicamente cualquier cosa.
 */
typedef struct cajitaInt CajitaInt;

struct cajitaInt {
  int data;
  CajitaInt *sig,*ant;
};

typedef struct {
  CajitaInt *head,*tail;
  int size;
} ListaInt;
/*FIN del tipo ListaInt.*/

/*INICIO Funciones y Procedimientos referentes al tipo ListaInt*/
/**
 * Crea una nueva Cajita, reservando la memoria necesaria para ello.
 * 
 * retorna: Un nuevo apuntador a Cajita vacía.
 */
CajitaInt *newCajitaInt();

/**
 * Crea una nueva lista vacía, reservando la memoria necesaria para ello.
 * 
 * retorna: un nuevo apuntador a una lista vacía.
 */
ListaInt *newListaInt();


/**
 * Inserta el elemento 'elem' en la Lista '*list'
 * 
 * *list: apuntador a la Lista donde se desea hacer la inserción.
 * 
 * elem: elemento a insertar en la Lista.
 * 
 * retorna: Un entero que indica el estado de la inserción; 0 si fue realizada 
 *          con éxito, 1 en caso contrario.
 */
int add(ListaInt *list, int elem);

/**
 * Elimina el elemento 'elem' en la Lista '*list'
 * 
 * *list: apuntador a la Lista donde se desea hacer la eliminación.
 * 
 * elem: elemento a eliminar de la Lista.
 */
void delete(ListaInt *list,  int elem);

/**
 * Dice si un elemento 'elem' está actualmente o no en la Lista '*list'.
 * 
 * *list: apuntador a la Lista donde se desea hacer la búsqueda.
 * 
 * elem: elemento a buscar en la Lista.
 * 
 * retorna: Un entero que indica el estado de la búsqueda; 1 si se encontró el
 *          elemento, 1 en caso contrario.
 */

int isIn(ListaInt *list, int elem);


/**
 * Imprime en la salida estándar la ListaInt 'lista'.
 * 
 * lista: ListaInt a imprimir.
 */
void li_print(ListaInt lista);


/**
 * Se encarga de devolver una ListaInt a su estado original vacía, liberando la
 * memoria consumida por ésta.
 * 
 * lote: Un apuntador a la ListaInt que se desea liberar.
 * 
 * retorna: 0 si se completó la limpieza con éxito, 1 en caso contrario.
 */
int li_liberar(ListaInt *lista);

/*FIN Funciones y Procedimientos referentes al tipo ListaInt*/

/*----------------------------------------------------------------------------*/


/*FIN DEL ARCHIVO (EOF)*/
