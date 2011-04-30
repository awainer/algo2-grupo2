#include "a_sintactico.h"
#include "constr_tweets.h"
#include "cola.h"
#include "dict.h"
#include <stdio.h>
#include <stdlib.h>

#define OOM 5
#define  ERROR_CONTEXTO 6

/***Pendientes: ***/
/* convertir los numeros a string para guardarlos en un valor de diccionario */
/* chequear en todas las callbacks que el tweet este inicializado != SIN_INICIAR, chequeo semantico*/


int Tconstructor_Crear(Tconstructor* tc) {
    tc->estado=SIN_INICIAR;
    return 0;
}

int Tconstructor_Destruir(Tconstructor* tc){
    free(tc->buffer_dict);
    free(tc->buff_v);
    free(tc->buff_k);
    return 0;
}


int Tconstructor_setCola(Tconstructor *tc, TCola* cola){
    tc->colaDestino=cola;
    return 0;
}



int Tconstructor_eventoComienzaArray(Tconstructor* tc, void* dato){
if (tc->estado==SIN_INICIAR)
{
    tc->estado=AFUERA;
    return 0;
}
else
    return ERROR_CONTEXTO;

}

int Tconstructor_eventoTerminaArray (Tconstructor* tc, void* dato) {
    if(tc->estado==AFUERA)
    {
    tc->estado=SIN_INICIAR;
    return 0;
    }
    else
        {
        return ERROR_CONTEXTO;
        }

}

int Tconstructor_eventoComienzaObjeto(Tconstructor* tc, void* dato){

switch (tc->estado)
{
    case AFUERA : tc->estado=TWEET;
                  tc->buffer_dict=(TDiccionario *)malloc(sizeof(TDiccionario));
                  TDiccionaro_Crear(tc->buffer_dict);

                  break;
    case TWEET  : tc->estado=USER;
                  break;
    case SIN_INICIAR : return ERROR_CONTEXTO;
}

return 0;
}

int Tconstructor_push_par(Tconstructor* tc)
{/* Pasa el par k/v del buffer al buffer diccionario*/
    TDiccionario_colocar(tc->buffer_dict,tc->buff_k,tc->buff_v);
    free(tc->buff_k);
    free(tc->buff_v);
    return 0;
}

int Tconstructor_eventoTerminaObjeto(Tconstructor* tc, void* dato) {

if(tc->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}


switch (tc->estado)
{
    case USER   : tc->estado=TWEET;
                  break;
    case TWEET  : tc->estado=AFUERA; /* cuando termina un tweet coloco en la cola y creo un nuevo dict*/
                  C_Agregar(tc->colaDestino,tc->buffer_dict);
                  tc->buffer_dict=(TDiccionario *)malloc(sizeof(TDiccionario));
                  if (tc->buffer_dict==NULL)
                    return OOM;
                  TDiccionaro_Crear(tc->buffer_dict);
                  break;

}
return 0;
}


int Tconstructor_eventoClave(Tconstructor* tc, void* dato) {
if(tc->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}

    if(tc->estado==TWEET)
    {

    tc->buff_k=(char *)malloc(strlen(dato)+1);
    }
    else if (tc->estado==USER)
    { /*Las claves dentro del objeto user pasan a ser user_clave */
    tc->buff_v=(char *)malloc(strlen(dato)+strlen("user_")+1);
    tc->buff_v[0]=0; /*aca inicializo el string buffer, le pongo el user_ y el dato */
    strcat(tc->buff_v,"user_");
    strcat(tc->buff_v,dato);
    Tconstructor_push_par(tc);
    }

    if (tc->buff_k==NULL)
    {
        Tdiccionario_Destruir(tc->buffer_dict);
        free(tc->buffer_dict);
        return OOM;
    }

    strcpy(tc->buff_k,dato);
    return 0;
}


int Tconstructor_eventoNumero(Tconstructor* tc, void* dato) {
if(tc->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    tc->buff_v=(char *)malloc(20); /*Esto es arbitrario, habria que cambiarlo 20 caracteres es el numero mas grande que se puede escribir con 64bits*/
    if (tc->buff_v==NULL)
    {   Tdiccionario_Destruir(tc->buffer_dict);
        free(tc->buffer_dict);
        free(tc->buff_v);
        return OOM;
    }
    sprintf(tc->buff_v,"%d",dato);
    Tconstructor_push_par(tc);
    return 0;
}


int Tconstructor_eventoString(Tconstructor* tc, void* dato) {
if(tc->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    tc->buff_v=(char *)malloc(strlen(dato)+1);
    if (tc->buff_v==NULL)
        return OOM;

    strcpy(tc->buff_v,dato);
    Tconstructor_push_par(tc);
    return 0;
}

int Tconstructor_eventoNull(Tconstructor* tc, void* dato) {
if(tc->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    tc->buff_v=(char *)malloc(5);
        if (tc->buff_v==NULL)
        {   Tdiccionario_Destruir(tc->buffer_dict);
            free(tc->buffer_dict);
            free(tc->buff_v);
            return OOM;
        }
    strcpy(tc->buff_v,"Null");
    Tconstructor_push_par(tc);
    return 0;
}

int Tconstructor_eventoTrue(Tconstructor* tc, void* dato) {
if(tc->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    tc->buff_v=(char *)malloc(6);
        if (tc->buff_v==NULL)
        {   Tdiccionario_Destruir(tc->buffer_dict);
            free(tc->buffer_dict);
            free(tc->buff_v);
            return OOM;
        }
    strcpy(tc->buff_v,"True");
    Tconstructor_push_par(tc);
    return 0;

}

int Tconstructor_eventoFalse(Tconstructor* tc, void* dato) {
if(tc->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    tc->buff_v=(char *)malloc(6);
         if (tc->buff_v==NULL)
        {   Tdiccionario_Destruir(tc->buffer_dict);
            free(tc->buffer_dict);
            free(tc->buff_v);
            return OOM;
        }
    strcpy(tc->buff_v,"False");
    Tconstructor_push_par(tc);
    return 0;
}
