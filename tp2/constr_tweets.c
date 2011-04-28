#include "a_sintactico.h"
#include "constr_tweets.h"
#include "cola.h"
#include "dict.h"
#include <stdio.h>
#include <stdlib.h>

#define OOM 5
#define  SIN_INICIALIZAR 6



int Tconstructor_Crear(Tconstructor* tc) {
    tc->estado=SIN_INICIAR;
    tc->buffer_dict=(TDiccionario *)malloc(sizeof(TDiccionario));
    TDiccionaro_Crear(tc->buffer_dict);

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
    return SIN_INICIALIZAR;

}

int Tconstructor_eventoTerminaArray (Tconstructor* tc, void* dato) {
    if(tc->estado==AFUERA)
    {
    tc->estado=SIN_INICIAR;
    return 0;
    }
    else
        return SIN_INICIALIZAR;


}

int Tconstructor_eventoComienzaObjeto(Tconstructor* tc, void* dato){

switch (tc->estado)
{
    case AFUERA : tc->estado=TWEET;
                  break;
    case TWEET  : tc->estado=USER;
                  break;
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
    tc->buff_k=(char *)malloc(strlen(dato)+1);
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
    /******TODO: aca tenemos que convertir numeros a string*******/
    tc->buff_v=(char *)malloc(5);
    if (tc->buff_v==NULL)
    {   Tdiccionario_Destruir(tc->buffer_dict);
        free(tc->buffer_dict);
        free(tc->buff_v);
        return OOM;
    }

    strcpy(tc->buff_v,"numb");
    Tconstructor_push_par(tc);
    return 0;
}


int Tconstructor_eventoString(Tconstructor* tc, void* dato) {

    if(tc->estado==TWEET)
    {
    tc->buff_v=(char *)malloc(strlen(dato)+1);
    if (tc->buff_v==NULL)
        return OOM;

    strcpy(tc->buff_v,dato);
    Tconstructor_push_par(tc);
    return 0;
    } else if (tc->estado==USER)
    {
        tc->buff_v=(char *)malloc(strlen(dato)+strlen("user_")+1);

        if (tc->buff_v==NULL)
        {   Tdiccionario_Destruir(tc->buffer_dict);
            free(tc->buffer_dict);
            free(tc->buff_v);
            return OOM;
        }

        tc->buff_v[0]=0;
        strcat(tc->buff_v,"user_");
        strcat(tc->buff_v,dato);
        Tconstructor_push_par(tc);
    }
return 0;
}

int Tconstructor_eventoNull(Tconstructor* tc, void* dato) {
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
