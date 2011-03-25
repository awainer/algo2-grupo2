#ifndef PARSER_H_
#define PARSER_H_

#include "a_sintactico.h"
#include "a_lexico.h"
#include <stdlib.h>


typedef struct t_parser{
	TSintactico as;
	TLexico lex;
	/*FILE*	arch;*/
}TParser;

/*int TParser_Crear(TSintactico*  ts,TLexico * tl,FILE * arch,TParser * parser);*/
int TParser_Crear(TSintactico*  ts,TLexico * tl, TParser * parser);
int TParser_Parsear(TParser * parser);
int TParser_Destruir(TParser * parser);
#endif

