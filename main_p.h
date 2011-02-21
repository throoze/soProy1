/* Archivo: main_p.h
 * Proceso maestro.
 * HEADER
 * Autores: Victor De Ponte
 *          Isaac Lopez
 */

#ifndef STD
#define STD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

struct timeval start, end;

/*----------------------------------------------------------------------------*/

/*INICIO Funciones y procedimientos referentes al manejo de respuestas*/
/**
 * Se encarga de leer los archivos que construyen los hijos con las soluciones
 * conseguidas.
 * respuestas: Apuntador al Trie que almacenará las respuestas.
 */
void lectura(Trie *respuestas, int nJobs);

/*FIN Funciones y procedimientos referentes al manejo de respuestas*/
/*----------------------------------------------------------------------------*/
/*FIN DEL ARCHIVO (EOF)*/
