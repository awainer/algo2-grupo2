
#include "token.h"
#include "a_sintactico.h"




int TSintactico_Crear(TSintactico* as){
    as->error_codigo=0;
    as->tValidos[0]=TOKEN_OBJETO_EMPIEZA;
    as->tValidos[1]=TOKEN_NULL;
    return 0;
    }

int TSintactico_PushToken(TSintactico* as, Token* token){
    int i=0;

    while(as->tValidos[i] != TOKEN_NULL){
        /* logica de sintaxis*/


        }

    return 0;
    }


int TSintactico_terminarFlujo(TSintactico* as){
    return 0;
    }



int TSintactico_getUltimoError(TSintactico*  as, int *codigo, char* mensaje){
    return 0;
    }
