#ifndef CONSTR_TWEETS_H_INCLUDED
#define CONSTR_TWEETS_H_INCLUDED

#include "a_sintactico.h"
#include "cola.h"
#include "dict.h"

typedef enum estadosTweet{
    AFUERA,
    TWEET,
    USER,
    SIN_INICIAR
}estadosTweet;

typedef struct _t_constructor{
    TDiccionario * buffer_dict;
    char * buff_k;
    char * buff_v;
    TCola * colaDestino;
    int  estado;
}Tconstructor;

/*
Descripci�n: Crea constructor de tweets.
Precondici�n: ninguna
Postcondici�n: el constructor de tweets ha sido creado.
*/

int Tconstructor_Crear(void* tc);

/*
Descripci�n: Libera los recursos asociados del constructor.
Precondiciones: El Constructor ha sido creado.
Postcondiciones: Se liberan recursos asociados.
*/
int Tconstructor_Destruir(void* tc);

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

int Tconstructor_eventoComienzaArray(void * tc, void* dato);

int Tconstructor_eventoTerminaArray(void* tc, void* dato);

int Tconstructor_eventoComienzaObjeto(void* tc, void* dato);

int Tconstructor_eventoTerminaObjeto(void* tc, void* dato);

int Tconstructor_eventoClave(void* tc, void* dato);

int Tconstructor_eventoNumero(void* tc, void* dato);

int Tconstructor_eventoString(void* tc, void* dato);

int Tconstructor_eventoNull(void* tc, void* dato);

int Tconstructor_eventoTrue(void* tc, void* dato);

int Tconstructor_eventoFalse(void* tc, void* dato);



#endif
