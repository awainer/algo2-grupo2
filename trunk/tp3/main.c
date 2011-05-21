#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"
#include "a_sintactico.h"
#include "a_lexico.h"
#include "parser.h"
#include "dict.h"
#include "constr_tweets.h"
#include "LsO.h"


int comparar_dicts(void* v1, void* v2)
{
    TDiccionario *d1,*d2;
    int aux;
    char * buffer1, * buffer2;

    d1=(TDiccionario*)v1;
    d2=(TDiccionario*)v2;

    aux=TDiccionario_sizeDato(d1,"user_screen_name");
    buffer1=(char*)malloc(aux);
    TDiccionario_obtener(d1,"user_screen_name",buffer1);
    aux=TDiccionario_sizeDato(d2,"user_screen_name");
    buffer2=(char*)malloc(aux);
    TDiccionario_obtener(d2,"user_screen_name",buffer2);
    aux=strcmp(buffer1,buffer2);
    free(buffer1);
    free(buffer2);
    return aux;

}



int main(int argc, char * argv[])
{


    TDiccionario * miDiccionario=NULL;
    TCola colaTweets;
    Tconstructor miConstructor;
    TParser miParser;
    TListaOrdenada miListaOrdenada;
    int flag;
    FILE *  archivo;
    char    c;
    int    error=E_NONE,sizeDato,i=0;

    char * nuevo=NULL, * actual=NULL;

    /*int  i,cant_elementos ;*/


    /*Inicializo el constructor con su cola*/
    Tconstructor_Crear(&miConstructor);
    C_Crear(&colaTweets,sizeof(TDiccionario));
    Tconstructor_setCola(&miConstructor,&colaTweets);
    TParser_Crear(&miParser);

    TParser_setCallback(&miParser,CB_COMIENZA_ARRAY,&miConstructor,Tconstructor_eventoComienzaArray);
    TParser_setCallback(&miParser,CB_TERMINA_ARRAY,&miConstructor,Tconstructor_eventoTerminaArray);
    TParser_setCallback(&miParser,CB_COMIENZA_OBJETO,&miConstructor,Tconstructor_eventoComienzaObjeto);
    TParser_setCallback(&miParser,CB_TERMINA_OBJETO,&miConstructor,Tconstructor_eventoTerminaObjeto);
    TParser_setCallback(&miParser,CB_CLAVE,&miConstructor,Tconstructor_eventoClave);
    TParser_setCallback(&miParser,CB_TRUE,&miConstructor,Tconstructor_eventoTrue);
    TParser_setCallback(&miParser,CB_FALSE,&miConstructor,Tconstructor_eventoFalse);
    TParser_setCallback(&miParser,CB_NULL,&miConstructor,Tconstructor_eventoNull);
    TParser_setCallback(&miParser,CB_NUMERO,&miConstructor,Tconstructor_eventoNumero);
    TParser_setCallback(&miParser,CB_STRING,&miConstructor,Tconstructor_eventoString);

    archivo=fopen(argv[1],"r");

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
    /*Saco de la cola y meto en la lista ordenada*/
    miDiccionario=(TDiccionario*)malloc(sizeof(TDiccionario));
    LO_Crear(&miListaOrdenada,sizeof(TDiccionario),comparar_dicts);
    while ( !C_Vacia(colaTweets)) {
        C_Sacar(&colaTweets,miDiccionario);
        LO_Insertar(&miListaOrdenada,miDiccionario);
        }

if(!LO_Vacia(miListaOrdenada))
{

        LO_Mover_Cte(&miListaOrdenada,L_Primero);
        LO_Elem_Cte(miListaOrdenada,miDiccionario);
        sizeDato=TDiccionario_sizeDato(miDiccionario,"user_screen_name");

        actual=(char *)malloc(sizeDato);
        TDiccionario_obtener(miDiccionario,"user_screen_name",actual);
        /*nuevo=(char *)malloc(sizeDato);
        TDiccionario_obtener(miDiccionario,"user_screen_name",nuevo);*/

            flag=TRUE;
            while(flag)
            {
                i=0;
                /*free(actual);*/
               if(nuevo!=NULL)
                    free(nuevo);
                nuevo=(char *)malloc(strlen(actual)+1);
                TDiccionario_obtener(miDiccionario,"user_screen_name",nuevo);

                while(flag && (!strcmp(actual,nuevo)))
                {                        i++;

                    flag=LO_Mover_Cte(&miListaOrdenada,L_Siguiente);
                    if(flag)
                    {
                        free(actual);
                        LO_Elem_Cte(miListaOrdenada,miDiccionario);
                        sizeDato=TDiccionario_sizeDato(miDiccionario,"user_screen_name");
                        actual=(char *)malloc(sizeDato);
                        TDiccionario_obtener(miDiccionario,"user_screen_name",actual);
                    }
                }
               if(i>=2)
                    printf(" %s %d\n",nuevo,i);

            }

}
}

    LO_Mover_Cte(&miListaOrdenada,L_Primero);
    do{
        LO_Elem_Cte(miListaOrdenada,miDiccionario);
        Tdiccionario_Destruir(miDiccionario);

    }while(LO_Mover_Cte(&miListaOrdenada,L_Siguiente));


    LO_Destruir(&miListaOrdenada);


        if(nuevo!=NULL)
            free(nuevo);
        if(actual!=NULL)
            free(actual);

    free(miDiccionario);
    fclose(archivo);
    Tconstructor_Destruir(&miConstructor);
    TParser_destruir(&miParser);

    return 0;

}

