
#include "token.h"
#include "a_sintactico.h"




int TSintactico_Crear(TSintactico* as){
    as->error_codigo=0;
    as->tValidos[0]=TOKEN_OBJETO_EMPIEZA;
    as->tValidos[1]=TOKEN_NULL;
    as->Tstring=1;
    return 0;
    }

int TSintactico_PushToken(TSintactico* as, Token* token){
   /* int i=0;
    while(TOKEN_NULL != token->tipo){
        switch (token->tipo){
        case TOKEN_STRING:  while (i<=2)
                                if((as->tValidos[i] == token->tipo) && (as->Tstring == 1)){
                                    as->tValidos=[TOKEN_DOSPUNTOS,TOKEN_NULL]
                                    printf("clave");
                                    as->Tstring = 2;
                                    }
                                    else
                                        i++;
                            if(i == 2)
                                printf(("error"));
                            break;





        case TOKEN_NUMERO,
        case TOKEN_OBJETO_EMPIEZA:   while (i<=1)
                                            if(as->tValidos[i] == token->tipo){
                                                as->tValidos=[TOKEN_OBJETO_TERMINA,TOKEN_STRING,TOKEN_NULL]
                                                printf("objeto\n\t");
                                            }
                                        else
                                            i++;
                                     if(i == 2)
                                        printf(("error"));
                                     break;

        case TOKEN_OBJETO_TERMINA,
        case TOKEN_ARRAY_EMPIEZA,
        case TOKEN_ARRAY_TERMINA,
        case TOKEN_COMA,
        case TOKEN_DOSPUNTOS,
        case TOKEN_TRUE,
        case TOKEN_FALSE,

        */


    return 0;
    }


int TSintactico_terminarFlujo(TSintactico* as){
    return 0;
    }



int TSintactico_getUltimoError(TSintactico*  as, int *codigo, char* mensaje){
    return 0;
    }
