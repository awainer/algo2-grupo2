/*Implementaciones del TDA TLexico*/

#include "a_lexico.h"
#include <string.h>


int TLexico_Crear(TLexico* al){
    al->error_codigo=0;
    return 0;
}

int TLexico_setAnalizadorSintactico(TLexico* al, TSintactico* as){
    al-> sintactico = as;
    return 0;
}

int TLexico_PushChar(TLexico* al, char c){
    Token token;
    /* el hecho de que C no soporte rangos hace esta implementacion mas bien engorrosa*/
if ( (( c >= 'a' )&&( c <= 'z' ) ) || ( (c>='A') && (c<='Z') )){
    token.tipo=TOKEN_STRING;
	}	else if((c>='0') && (c<='9')) {
        token.tipo=TOKEN_NUMERO;
        }
        else if(c=='{')
            token.tipo=TOKEN_OBJETO_EMPIEZA;
        else if(c=='}')
            token.tipo=TOKEN_OBJETO_TERMINA;
        else if(c=='[')
            token.tipo=TOKEN_ARRAY_EMPIEZA;
        else if(c==']')
            token.tipo=TOKEN_ARRAY_TERMINA;
        else if(c==',')
            token.tipo=TOKEN_COMA;
        else if(c=='"')
            token.tipo=TOKEN_COMILLA;
        else if(c==',')
            token.tipo=TOKEN_DOSPUNTOS;
        else{
            al->error_codigo=1;
           /* al->error_mensaje="El caracter recibido no tiene un token asociado";*/
           strcpy(al->error_mensaje,"Caracter no valido");
           return 1;
        }
    strcpy(token.dato,&c);
    TSintactico_PushToken(al->sintactico,&token);
return 0;
}



int TLexico_terminarFlujo(TLexico* al){
    return 0;
}

int TLexico_getUltimoError(TLexico* al, int  * codigo, char* mensaje){
    return 0;
}


