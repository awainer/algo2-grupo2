#include "a_sintactico.h"
#include "constr_tweets.h"
#include "cola.h"
#include "dict.h"
#include <stdio.h>





int Tconstructor_Crear(Tconstructor* tc) {
    TDiccionaro_Crear(&tc->Buffer);
    tc->estado=FUERA;
    return 0;
}

int Tconstructor_Destruir(Tconstructor* tc){
    Tdiccionario_Destruir(&tc->Buffer);
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

switch tc->estado
{
    case AFUERA : tc->estado=TWEET;
                  break;
    case TWEET  : tc->estado=USER;
                  break;
}

return ;
}


void Tconstructor_eventoTerminaObjeto(Tconstructor* tc, void* dato) {

switch tc->estado
{
    case USER   : tc->estado=TWEET;
                  break;
    case TWEET  : tc->estado=AFUERA;
                  C_Agregar(tc->colaDestino,tc->Buffer);

                  break;

}
return;
}


void Tconstructor_eventoClave(Tconstructor* tc, void* dato) {

return ;
}


void Tconstructor_eventoNumero(Tconstructor* tc, void* dato) {

return ;
}


void Tconstructor_eventoString(Tconstructor* tc, void* dato) {
return ;
}

void Tconstructor_eventoNull(Tconstructor* tc, void* dato) {
return ;
}

void Tconstructor_eventoTrue(Tconstructor* tc, void* dato) {

return ;
}

void Tconstructor_eventoFalse(Tconstructor* tc, void* dato) {

return ;
}
