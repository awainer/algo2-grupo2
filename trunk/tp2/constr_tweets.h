#ifndef CONSTR_TWEETS_H_INCLUDED
#define CONSTR_TWEETS_H_INCLUDED

#include "a_sintactico.h"
#include "cola.h"
#include "dict.h"

typedef enum estadosTweet{
    FUERA,
    TWEET,
    USER
}estadosTweet;

typedef struct _t_constructor{
    TDiccionario Buffer;
    TCola * colaDestino;
    int  estado;
}Tconstructor;

/*
Descripci�n: Crea constructor de tweets.
Precondici�n: ninguna
Postcondici�n: el constructor de tweets ha sido creado.
*/

int Tconstructor_Crear(Tconstructor* tc);

/*
Descripci�n: Libera los recursos asociados del constructor.
Precondiciones: El Constructor ha sido creado.
Postcondiciones: Se liberan recursos asociados.
*/
int Tconstructor_Destruir(Tconstructor* tc);

/*
Descripci�n: Establece la Cola donde se colocar�n los Tweets en formato TDiccionario.
Precondiciones: el constructor ha sido creado.
Postcondiciones: Se establece la estructura de cola donde se colocar�n los tweets en formato TDiccionario.
*/
int Tconstructor_setCola(Tconstructor *tc, TCola* cola);

/*
Descripci�n: se procesa el evento ocurrido.
Precondiciones: El constructor ha sido creado y se le ha establecido una cola.
Postcondiciones: se procesa el evento ocurrido.
*/

void Tconstructor_eventoComienzaArray(Tconstructor* tc, void* dato);

void Tconstructor_eventoTerminaArray(Tconstructor* tc, void* dato);

void Tconstructor_eventoComienzaObjeto(Tconstructor* tc, void* dato);

void Tconstructor_eventoTerminaObjeto(Tconstructor* tc, void* dato);

void Tconstructor_eventoClave(Tconstructor* tc, void* dato);

void Tconstructor_eventoNumero(Tconstructor* tc, void* dato);

void Tconstructor_eventoString(Tconstructor* tc, void* dato);

void Tconstructor_eventoNull(Tconstructor* tc, void* dato);

void Tconstructor_eventoTrue(Tconstructor* tc, void* dato);

void Tconstructor_eventoFalse(Tconstructor* tc, void* dato);



#endif
