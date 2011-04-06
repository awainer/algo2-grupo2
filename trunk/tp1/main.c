#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "a_sintactico.h"
#include "a_lexico.h"
#include "parser.h"

#include <string.h>

int main(int argc, char * argv[])
{
    TLexico  tl;
    TSintactico  ts;
    TParser miParser;
    char   mensaje_error[50];
    int    codigo_error;




    TParser_Crear(&ts,&tl,argv[1],&miParser);
    TParser_Parsear(&miParser);

    mensaje_error[0]=0; /* esto es para evitar el warning de que usamos la variable sin inicializar*/
    /* */
    TParser_getUltimoError(&miParser,&codigo_error,mensaje_error);
    switch(codigo_error)
    {
        case E_LEXICO : printf("Error lexico: %s \n",mensaje_error);
                        break;
        case E_SINTACTICO : printf("Error sintactico: %s\n",mensaje_error);
                            break;
    }

    TParser_Destruir(&miParser);


    return 0;
}

