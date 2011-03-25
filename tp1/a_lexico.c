/*Implementaciones del TDA TLexico*/

#include "a_lexico.h"
#include <string.h>


int TLexico_Crear(TLexico* al){
    al->error_codigo=0;
/*TODO: ver porque esto no complila*/
 /*   al->error_mensaje="S";*/

    return 0;
}

int TLexico_setAnalizadorSintactico(TLexico* al, TSintactico* as){
    al-> sintactico = as;
    return 0;
}

int TLexico_PushChar(TLexico* al, char c){
    Token token;
if (( c > 'a' ) && ( c < 'z' )){
    /*el caracter es una letra minuscula*/

    token.tipo=TOKEN_STRING;
    strcpy(token.dato,&c);
	}

return 0;
}



int TLexico_terminarFlujo(TLexico* al){
    return 0;
}

int TLexico_getUltimoError(TLexico* al, int  * codigo, char* mensaje){
    return 0;
}


