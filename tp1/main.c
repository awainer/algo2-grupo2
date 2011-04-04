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

    /*setbuf(stdout, NULL);*/



    TParser_Crear(&ts,&tl,argv[1],&miParser);
    TParser_Parsear(&miParser);
    TParser_Destruir(&miParser);


/*    char cadena[20];
    int i;
    strcpy(cadena,":{\"nombre1234\":,1234,\"unarray\":[\"mingo\",\"anibal\"]}");
    TLexico_Crear(&tl);
    TSintactico_Crear(&ts);
    TLexico_setAnalizadorSintactico(&tl,&ts);



 Codigo para probar TLexico
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
*/
    return 0;
}

