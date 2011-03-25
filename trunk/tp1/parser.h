#ifndef PARSER_H_
#define PARSER_H_

#include "a_sintactico.h"
#include "a_lexico.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    E_NONE,
    E_LEXICO,
    E_SINTACTICO
}TipoError;

typedef struct t_parser{
	TSintactico * as;
	TLexico  * lex;
    TipoError ultimoError;
}TParser;

int TParser_Crear(TSintactico*  ts,TLexico * tl, char * archivo, TParser * parser);
int getUltimoError(TParser * parser);
int TParser_Parsear(TParser * parser);
int TParser_Destruir(TParser * parser);
#endif

