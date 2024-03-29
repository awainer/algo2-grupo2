#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a_sintactico.h"




int TParser_Crear(TParser* p)
{
    TLexico_Crear(&p->lex);
    TSintactico_Crear(&p->as);
    TLexico_setAnalizadorSintactico(&p->lex,&p->as);
    p->ultimoError=E_NONE;
    return 0;
}

int TParser_PushChar(TParser* p, char c)
{   /*printf("%c\n",c);*/
    int e=0;

    e=TLexico_PushChar(&p->lex,c);
    if(e!=0)
        {printf("error %d\n",e);
        printf("error %d\n",c);}
    return e;

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

int TParser_setCallback (TParser *p, int evento, void* tda_contexto, int(*callback)( void*,  void*))
{
    /*ts->arrayCallbacks[evento].cb=callback;
    ts->arrayCallbacks[evento].contexto=tda_contexto;*/
   Tsintactico_setCallback(&p->as,evento,tda_contexto,callback);

    return 0;
}
int TParser_destruir(TParser *p)
{
    Tsintactico_Destruir(&p->as);
    return 0;
}



