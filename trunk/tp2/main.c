#include <stdlib.h>
#include <stdio.h>

#include "constr_tweets.h"
#include "token.h"
#include "a_sintactico.h"
#include "a_lexico.h"
#include "parser.h"

#include <string.h>

int main(int argc, char * argv[])
{

    TParser miParser;
    FILE *  archivo;
    char    c;
    char    error_desc[50];
    int     error=E_NONE;

    archivo=fopen(argv[1],"r");
    TParser_Crear(&miParser);

    if(archivo==NULL)
    {
        printf("No puedo abrir el archivo\n");
        return -1;
    }

    c=getc(archivo);

    while( (c!=EOF) && (error==E_NONE) )
    {
        error=TParser_PushChar(&miParser,c);
        c=getc(archivo);
    }

    if(error==E_NONE)
    {
        error=TParser_terminarFlujo(&miParser);
    }

    if(error!=E_NONE)
    {
        TParser_getUltimoError(&miParser,&error,error_desc);
        switch(error)
        {
            case E_LEXICO : printf("ERROR LEXICO: %s",error_desc);
                            break;
            case E_SINTACTICO : printf("ERROR SINTACTICO: %s",error_desc);
                            break;
        }
    fclose(archivo);
    return 1;
    }

    fclose(archivo);
    return 0;

}

