#include "parser.h"
#include <stdlib.h>
int TParser_Crear(TSintactico*  ts,TLexico * tl,FILE * archivo, TParser * parser){
	parser->as=ts;
	parser->lex=tl;
    parser->ultimoError=E_NONE;
    return 0;
}
int TParser_Parsear(TParser * parser){
    char c;
    /*while((c!=EOF) && (parser->ultimoError = E_NONE)){
    pushCharLexico
    }*/

    return 0;
}

int getUltimoError(TParser * parser){

    return 0;
}
int TParser_Destruir(TParser * parser){
    return 0;
}
