#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




int TParser_Crear(TParser* p)
{
    TLexico_Crear(&p->lex);
    TSintactico_Crear(&p->as);
    TLexico_setAnalizadorSintactico(&p->lex,&p->as);
    p->ultimoError=E_NONE;
    return 0;
}

int TParser_PushChar(TParser* p, char c)
{
    return TLexico_PushChar(&p->lex,c);

}

int TParser_terminarFlujo(TParser* p)
{
    return TLexico_terminarFlujo(&p->lex);
}


int TParser_getUltimoError(TParser* p, int * codigo, char* mensaje)
{
    TLexico_getUltimoError(&p->lex,codigo,mensaje);
    if(*codigo==E_LEXICO)
        return 0;
    else
    {
        TSintactico_getUltimoError(&p->as,codigo,mensaje);
        return 0;
    }
}
