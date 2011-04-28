#include "a_sintactico.h"
#include "constr_tweets.h"
#include "cola.h"
#include "dict.h"
#include <stdio.h>
#include <stdlib.h>





int Tconstructor_Crear(Tconstructor* tc) {
    TDiccionaro_Crear(tc->buffer_dict);
    tc->estado=AFUERA;
    tc->buffer_dict=(TDiccionario *)malloc(sizeof(TDiccionario));
    return 0;
}

int Tconstructor_Destruir(Tconstructor* tc){
    /*Tdiccionario_Destruir(&tc->Buffer);*/
    return 0;
}


int Tconstructor_setCola(Tconstructor *tc, TCola* cola){
    tc->colaDestino=cola;
    return 0;
}



void Tconstructor_eventoComienzaArray(Tconstructor* tc, void* dato){

return ;
}

void Tconstructor_eventoTerminaArray (Tconstructor* tc, void* dato) {

return ;
}

void Tconstructor_eventoComienzaObjeto(Tconstructor* tc, void* dato){

switch (tc->estado)
{
    case AFUERA : tc->estado=TWEET;
                  break;
    case TWEET  : tc->estado=USER;
                  break;
}

return ;
}

void Tconstructor_push_par(Tconstructor* tc)
{/* Pasa el par k/v del buffer al buffer diccionario*/
    TDiccionario_colocar(tc->buffer_dict,tc->buff_k,tc->buff_v);
    free(tc->buff_k);
    free(tc->buff_v);
}

void Tconstructor_eventoTerminaObjeto(Tconstructor* tc, void* dato) {

switch (tc->estado)
{
    case USER   : tc->estado=TWEET;
                  break;
    case TWEET  : tc->estado=AFUERA; /* cuando termina un tweet coloco en la cola y creo un nuevo dict*/
                  C_Agregar(tc->colaDestino,(void*)&tc->buffer_dict);
                  tc->buffer_dict=(TDiccionario *)malloc(sizeof(TDiccionario));
                  TDiccionaro_Crear(tc->buffer_dict);
                  break;

}
return;
}


void Tconstructor_eventoClave(Tconstructor* tc, void* dato) {
    tc->buff_k=(char *)malloc(strlen(dato)+1);
    strcpy(tc->buff_k,dato);
    return ;
}


void Tconstructor_eventoNumero(Tconstructor* tc, void* dato) {
    /*itoa no es ansi, asi que puse una implementacion*/
    /*TODO: aca tenemos que convertir numeros a string*/
    tc->buff_v=(char *)malloc(5);
    strcpy(tc->buff_v,"numb");
    Tconstructor_push_par(tc);
    return ;
}


void Tconstructor_eventoString(Tconstructor* tc, void* dato) {

    if(tc->estado==TWEET)
    {
    tc->buff_v=(char *)malloc(strlen(dato)+1);
    strcpy(tc->buff_v,dato);
    Tconstructor_push_par(tc);
    return ;
    } else if (tc->estado==USER)
    {
        tc->buff_v=(char *)malloc(strlen(dato)+strlen("user_")+1);
        tc->buff_v[0]=0;
        strcat(tc->buff_v,"user_");
        strcat(tc->buff_v,dato);
        Tconstructor_push_par(tc);
    }

}

void Tconstructor_eventoNull(Tconstructor* tc, void* dato) {
    tc->buff_v=(char *)malloc(5);
    strcpy(tc->buff_v,"Null");
    Tconstructor_push_par(tc);
    return ;
}

void Tconstructor_eventoTrue(Tconstructor* tc, void* dato) {
    tc->buff_v=(char *)malloc(6);
    strcpy(tc->buff_v,"True");
    Tconstructor_push_par(tc);
    return ;

}

void Tconstructor_eventoFalse(Tconstructor* tc, void* dato) {
    tc->buff_v=(char *)malloc(6);
    strcpy(tc->buff_v,"False");
    Tconstructor_push_par(tc);
    return ;
}
