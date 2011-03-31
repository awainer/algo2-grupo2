#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "a_sintactico.h"
#include "a_lexico.h"
#include "parser.h"

#include <string.h>

int main(void)
{
    TLexico  tl;
    TSintactico  ts;
    char cadena[20];
    int i;
    strcpy(cadena,":{\"nombre1234\":1234a}");
    TLexico_Crear(&tl);
    TSintactico_Crear(&ts);
    TLexico_setAnalizadorSintactico(&tl,&ts);

    for(i=0; i<=strlen(cadena); i++)
    {
        printf("mando el caracter %c\n",cadena[i]);
        TLexico_PushChar(&tl,cadena[i]);
        if(tl.error_codigo!=0)
        {


            printf(tl.error_mensaje);
            break;
        }
    }
    return 0;
}

