#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

int TParser_Crear(TSintactico*  ts,TLexico * tl,char * archivo, TParser * parser){
	parser->as=ts;
	parser->lex=tl;
    parser->ultimoError=E_NONE;
    parser->fh=fopen(archivo,"r");

    printf("El archivo es%s",archivo);

    TLexico_Crear(parser->lex);
    TSintactico_Crear(parser->as);
    TLexico_setAnalizadorSintactico(parser->lex,parser->as);

    return 0;
}
int TParser_Parsear(TParser * parser){
    parser->c=getc(parser->fh);
    while((parser->c!=EOF) && (parser->ultimoError == E_NONE))
    {
        /*printf("%c",parser->c);*/
        TLexico_PushChar(parser->lex,parser->c);
        parser->c=getc(parser->fh);

    }

    return 0;
}

int getUltimoError(TParser * parser){

    return 0;
}
int TParser_Destruir(TParser * parser){
    fclose(parser->fh);
    return 0;
}
