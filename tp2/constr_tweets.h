#ifndef CONSTR_TWEETS_H_INCLUDED
#define CONSTR_TWEETS_H_INCLUDED

#include "a_sintactico.h"
#include "cola.h"
#include "dict.h"



typedef struct {
    Tconstructor *tc; /* Puntero a estructura TConstructor. */
    int Ecorrecto; /*indicara internamente si el formato del tweet es correcto o no*/
    TDiccionario *pd; /* Puntero a estructura TDiccionario */

}Tconstructor;

/*
Descripción: Crea constructor de tweets.
Precondición: ninguna
Postcondición: el constructor de tweets ha sido creado.
*/

int Tconstructor_Crear(Tconstructor* tc);

/*
Descripción: Libera los recursos asociados del constructor.
Precondiciones: El Constructor ha sido creado.
Postcondiciones: Se liberan recursos asociados.
*/
int Tconstructor_Destruir(Tconstructor* tc);

/*
Descripción: Establece la Cola donde se colocarán los Tweets en formato TDiccionario.
Precondiciones: el constructor ha sido creado.
Postcondiciones: Se establece la estructura de cola donde se colocarán los tweets en formato TDiccionario.
*/
int Tconstructor_setCola(Tconstructor *tc, TCola* cola);

/*
Descripción: se procesa el evento ocurrido.
Precondiciones: El constructor ha sido creado y se le ha establecido una cola.
Postcondiciones: se procesa el evento ocurrido.
*/
int TConstructor_eventoOcurrido (Tconstructor *tc, int evento, void* dato);


#endif // CONSTR_TWEETS_H_INCLUDED
