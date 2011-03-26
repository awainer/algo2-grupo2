/*Implementaciones del TDA TLexico*/

#include "a_lexico.h"
#include <string.h>


int TLexico_Crear(TLexico* al){
    al->error_codigo=0;
    al->buffer_idx=-1;
    al->token->tipo=TOKEN_NULL;

    return 0;
}

int TLexico_setAnalizadorSintactico(TLexico* al, TSintactico* as){
    al-> sintactico = as;
    return 0;
}

int TLexico_PushChar(TLexico* al, char c){

    /* el hecho de que C no soporte rangos hace esta implementacion mas bien engorrosa*/
/*if ( (( c >= 'a' )&&( c <= 'z' ) ) || ( (c>='A') && (c<='Z') )){
    token.tipo=TOKEN_STRING;
	}*/
	/*token.tipo=TOKEN_FALSE;*/

        if  (c=='"'){
            if (al->buffer_idx==-1){
                /*comienza un string*/
                al->buffer_idx=0;
                }

                else{ /* estoy recibiendo una comilla pero el buffer ya tenia datos, asi que
                  estoy terminando el string*/
                    al->buffer_idx=-1; /*reinicio el index*/
                    if (TSintactico_PushToken(al->sintactico,al->token)){
                        return 0;
                        }
                    else{
                    /*Analizador Sintactico me devolvio un error*/
                        al->error_codigo=1;
                        /*TODO cambiar esto por un strcpy
                        al->error_mensaje="el analizador sintactico me dio error";*/
                        return 2;
                        }
        }

if (al->buffer_idx > -1){
        if ( (( c >= 'a' )&&( c <= 'z' ) ) || ( (c>='A') && (c<='Z') ))
        {

            al->token->dato[al->buffer_idx]=c;
            al->buffer_idx++;
        }

        if((c>='0') && (c<='9')) {

            al->token->tipo=TOKEN_NUMERO;
            al->token->dato[al->buffer_idx]=c;
            al->buffer_idx++;
        }
}

        if(c=='{')
            al->token->tipo=TOKEN_OBJETO_EMPIEZA;
        else if(c=='}')
            al->token->tipo=TOKEN_OBJETO_TERMINA;
        else if(c=='[')
            al->token->tipo=TOKEN_ARRAY_EMPIEZA;
        else if(c==']')
            al->token->tipo=TOKEN_ARRAY_TERMINA;
        else if(c==',')
            al->token->tipo=TOKEN_COMA;
        else if(c==',')
            al->token->tipo=TOKEN_DOSPUNTOS;
        else{
            al->error_codigo=1;
           /* al->error_mensaje="El caracter recibido no tiene un token asociado";*/
           strcpy(al->error_mensaje,"Caracter no valido");
           return 1;
        }
    if(al->token->tipo==TOKEN_FALSE)
        return 0;
    else{
        TSintactico_PushToken(al->sintactico,al->token);
    }
 }
return 0;

}


int TLexico_terminarFlujo(TLexico* al){
    return 0;
}

int TLexico_getUltimoError(TLexico* al, int  * codigo, char* mensaje){
    return 0;
}


