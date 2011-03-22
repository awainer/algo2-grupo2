/*Implementaciones del TDA TLexico*/

#include "a_lexico.h"



int TLexico_Crear(TLexico* al){
	/* Esto se tiene que inicializar en la funcion setAnalizadorSintactico */

	al.sintactico = NULL;
	al.error.codigo=10;
	al.error.mensaje='';
    return 0;
}

int TLexico_setAnalizadorSintactico(TLexico* al, TSintactico* as){
    return 0;
}

int TLexico_PushChar(TLexico* al, char c){
    return 0;
}

int TLexico_terminarFlujo(TLexico* al){
    return 0;
}

int TLexico_getUltimoError(TLexico* al, int codigo, char* mensaje){
    return 0;
}


