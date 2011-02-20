/* Archivo: main_t.h
 * Proceso maestro, Version de hilos.
 * Autores: Victor De Ponte
 *          Isaac Lopez
 */

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

#include "pReinas.h"


#ifndef USO
#define USO "\nreinas_t: Resuelve el problema de las 8 reinas usando hilos POSIX.\n\nDesarrollado por:\n\tVictor De Ponte, Carnet 05-38087\n\tIsaac Lopez, Carnet 07-41120\n\nUSO:\n\n\tSintaxis:\n\n\t\treinas_t [-n <num_trabajadores>] [-i {1|0}]\n\n\tOpciones:\n\n\t\t-n\tNumero de hilos a resolver el problema. El valor por\n\t\t\tdefecto es 8.\n\t\t-i\tOpcion de impresión. Debe ir seguido de un 1 si se desea\n\t\t\tque cada hilo imprima su resultado, o 0 en caso contra-\n\t\t\trio. El valor por defecto es 0.\n\n"
#endif
