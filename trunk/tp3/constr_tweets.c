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


int Tconstructor_Crear(void* tc) {
    Tconstructor * aux;
    aux = (Tconstructor*)tc;
    aux->estado=SIN_INICIAR;
    return 0;
}

int Tconstructor_Destruir(void* tc){
    Tconstructor * aux;
    aux = (Tconstructor*)tc;
    if(aux->estado==AFUERA)
        free(aux->buffer_dict);
    /*free(aux->buffer_dict);
    free(aux->buff_v);
    free(aux->buff_k);*/
    return 0;
}


int Tconstructor_setCola(Tconstructor *tc, TCola* cola){
    tc->colaDestino=cola;
    return 0;
}



int Tconstructor_eventoComienzaArray(void* tc, void* dato){
Tconstructor * aux;
aux = (Tconstructor*)tc;

if (aux->estado==SIN_INICIAR)
{
    aux->estado=AFUERA;
    return 0;
}
else
    return ERROR_CONTEXTO;

}

int Tconstructor_eventoTerminaArray (void* tc, void* dato) {
Tconstructor * aux;
aux = (Tconstructor*)tc;

    if(aux->estado==AFUERA)
    {
    aux->estado=SIN_INICIAR;
    return 0;
    }
    else
        {
        return ERROR_CONTEXTO;
        }

}

int Tconstructor_eventoComienzaObjeto(void* tc, void* dato){
Tconstructor * aux;
aux = (Tconstructor*)tc;
switch (aux->estado)
{
    case AFUERA : aux->estado=TWEET;
                  aux->buffer_dict=(TDiccionario *)malloc(sizeof(TDiccionario));
                  TDiccionaro_Crear(aux->buffer_dict);
                  break;

    case TWEET  : break;

    case SIN_INICIAR : return ERROR_CONTEXTO;
}

return 0;
}

int Tconstructor_push_par(Tconstructor* tc)
{/* Pasa el par k/v del buffer al buffer diccionario*/
    /*Tconstructor * aux;
    aux = (Tconstructor*)tc;*/
    TDiccionario_colocar(tc->buffer_dict,tc->buff_k,tc->buff_v);
    free(tc->buff_k);
    free(tc->buff_v);
    return 0;
}

int Tconstructor_eventoTerminaObjeto(void* tc, void* dato) {
Tconstructor * aux;
aux = (Tconstructor*)tc;
if(aux->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}


switch (aux->estado)
{
    case USER   : aux->estado=TWEET;
                  break;

    case TWEET  : aux->estado=AFUERA; /* cuando termina un tweet coloco en la cola y creo un nuevo dict*/
                  C_Agregar(aux->colaDestino,aux->buffer_dict);
                  free(aux->buffer_dict);

                  /*aux->buffer_dict=(TDiccionario *)malloc(sizeof(TDiccionario));
                  if (aux->buffer_dict==NULL)
                    return OOM;
                  TDiccionaro_Crear(aux->buffer_dict);*/
                  break;


}
return 0;
}


int Tconstructor_eventoClave(void* tc, void* dato) {
Tconstructor * aux;
aux = (Tconstructor*)tc;

if(aux->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    if(!strcmp((char*)dato,"user"))
    {
        aux->estado=USER;
        return 0;
    }


    if(aux->estado==TWEET)
    {
        aux->buff_k=(char *)malloc(strlen(dato)+1);
        strcpy(aux->buff_k,dato);
    }
    else if (aux->estado==USER)
    { /*Las claves dentro del objeto user pasan a ser user_clave */
        aux->buff_k=(char *)malloc(strlen(dato)+strlen("user_")+2);
        aux->buff_k[0]=0; /*aca inicializo el string buffer, le pongo el user_ y el dato */
        strcat(aux->buff_k,"user_");
        strcat(aux->buff_k,dato);
        /*Tconstructor_push_par(aux);*/
    }

    if (aux->buff_k==NULL)
    {
        Tdiccionario_Destruir(aux->buffer_dict);
        free(aux->buffer_dict);
        return OOM;
    }

    /*strcpy(aux->buff_k,dato);*/
    return 0;
}


int Tconstructor_eventoNumero(void* tc, void* dato) {
Tconstructor * aux;
aux = (Tconstructor*)tc;

if(aux->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    aux->buff_v=(char *)malloc(20); /*Esto es arbitrario, habria que cambiarlo 20 caracteres es el numero mas grande que se puede escribir con 64bits*/
    if (aux->buff_v==NULL)
    {   Tdiccionario_Destruir(aux->buffer_dict);
        free(aux->buffer_dict);
        free(aux->buff_v);
        return OOM;
    }
    /*sprintf(aux->buff_v,"%d",dato);*/
    strcpy(aux->buff_k,dato);
    Tconstructor_push_par(aux);
    return 0;
}


int Tconstructor_eventoString(void* tc, void* dato) {
Tconstructor * aux;
char * aux_dato ;

aux = (Tconstructor*)tc;
aux_dato=(char*)dato;

if(aux->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    aux->buff_v=(char *)malloc(strlen(aux_dato)+1);
    if (aux->buff_v==NULL)
        return OOM;

    strcpy(aux->buff_v,aux_dato); /***TODO agregar check para el estado USER ***/
    Tconstructor_push_par(aux);
    return 0;
}

int Tconstructor_eventoNull(void* tc, void* dato) {
Tconstructor * aux;
aux = (Tconstructor*)tc;

if(aux->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    aux->buff_v=(char *)malloc(5);
        if (aux->buff_v==NULL)
        {   Tdiccionario_Destruir(aux->buffer_dict);
            free(aux->buffer_dict);
            free(aux->buff_v);
            return OOM;
        }
    strcpy(aux->buff_v,"Null");
    Tconstructor_push_par(aux);
    return 0;
}

int Tconstructor_eventoTrue(void* tc, void* dato) {
Tconstructor * aux;
aux = (Tconstructor*)tc;

if(aux->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    aux->buff_v=(char *)malloc(6);
        if (aux->buff_v==NULL)
        {   Tdiccionario_Destruir(aux->buffer_dict);
            free(aux->buffer_dict);
            free(aux->buff_v);
            return OOM;
        }
    strcpy(aux->buff_v,"True");
    Tconstructor_push_par(tc);
    return 0;

}

int Tconstructor_eventoFalse(void* tc, void* dato) {
Tconstructor * aux;
aux = (Tconstructor*)tc;

if(aux->estado==SIN_INICIAR)
{
    return ERROR_CONTEXTO;
}
    aux->buff_v=(char *)malloc(6);
         if (aux->buff_v==NULL)
        {   Tdiccionario_Destruir(aux->buffer_dict);
            free(aux->buffer_dict);
            free(aux->buff_v);
            return OOM;
        }
    strcpy(aux->buff_v,"False");
    Tconstructor_push_par(aux);
    return 0;
}
