#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int TParser_Crear(TSintactico*  ts,TLexico * tl,char * archivo, TParser * parser){
	parser->as=ts;
	parser->lex=tl;
    parser->ultimoError=E_NONE;
    parser->fh=fopen(archivo,"r");

    printf("El archivo es %s\n",archivo);

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
        parser->ultimoError=TLexico_PushChar(parser->lex,parser->c);
        parser->c=getc(parser->fh);

    }
    TParser_TerminarFlujo(parser);
    return 0;
}


int TParser_TerminarFlujo(TParser * p)
{
    return 0;
}

int TParser_getUltimoError(TParser* p, int * codigo, char* mensaje)
{

    *codigo=p->lex->error_codigo;
    switch(*codigo)
    {

    case E_NONE :        {
                         strcpy(mensaje,"No ha ocurrido ningun error");
                         break; /* Aca esta justificado el uso del break porque no puede tener dos codigos distintos */
                         }

    case E_LEXICO :      { /* error en el lexico*/
                         strcpy(mensaje,p->lex->error_mensaje);
                         break;
                         }

    case E_SINTACTICO :  { /* error en el sintactico*/
                         strcpy(mensaje,p->as->error_mensaje);
                         break;
                         }
    }
    return 0;
}
int TParser_Destruir(TParser * parser){
    fclose(parser->fh);
    return 0;
}
