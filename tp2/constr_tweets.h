#ifndef CONSTR_TWEETS_H_INCLUDED
#define CONSTR_TWEETS_H_INCLUDED

#include "a_sintactico.h"
#include "cola.h"
#include "dict.h"



typedef struct {
    int Ecorrecto; /*indicara internamente si el formato del tweet es correcto o no*/
    TCola cola;     /*cola para acumular los tweets nose si esta bien asi o si deberia ser un puntero*/
    Tdiccionario diccionario;




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
int Tconstructor_Destruir(TConstructor* tc);

/*
Descripción: Establece la Cola donde se colocarán los Tweets en formato TDiccionario.
Precondiciones: el constructor ha sido creado.
Postcondiciones: Se establece la estructura de cola donde se colocarán los tweets en formato TDiccionario.
*/
int Tconstructor_setCola(TConstructor *tc, TCola* cola);

/*
Descripción: se procesa el evento ocurrido.
Precondiciones: El constructor ha sido creado y se le ha establecido una cola.
Postcondiciones: se procesa el evento ocurrido.
*/
int TConstructor_eventoOcurrido (TConstructor *tc, int evento, void* dato);


#endif // CONSTR_TWEETS_H_INCLUDED
