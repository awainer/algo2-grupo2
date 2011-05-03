#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"
#include "a_sintactico.h"
#include "a_lexico.h"
#include "parser.h"
#include "dict.h"
#include "var_array.h"
#include "constr_tweets.h"

int main(int argc, char * argv[])
{

  /*   TParser miParser;
    FILE *  archivo;
   char    c;
    char    error_desc[50];
    int     error=E_NONE;*/

    TDiccionario * miDiccionario=NULL;
    TCola colaTweets;
    Tconstructor miConstructor;
    V_Array a;
    /*V_Array *pVArray;
    funccmp fcomp;*/
    TParser miParser;
    FILE *  archivo;
    char    c;
    int    error=E_NONE,sizeDato;
    char * buffer,*buffer2;
    int  i,cant_elementos ; /*para debug, borrar despues*/
/*    int i;*/  /*aca empiezan las variables del array, por las dudas las separo*/
  /*  int elem;*/


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
    {  /* printf("%c\n",c);*/
        error=TParser_PushChar(&miParser,c);
        c=getc(archivo);
    }



/*Esto es una prueba, escribe los screen_name de las cosas que va desencolando */
    VA_create(&a, sizeof(TDiccionario*));
    cant_elementos=0;
    miDiccionario=(TDiccionario*)malloc(sizeof(TDiccionario));

    while ( !C_Vacia(colaTweets)) {
        C_Sacar(&colaTweets,miDiccionario);

        VA_add(&a,(void*)miDiccionario);
        /*Tdiccionario_Destruir(miDiccionario);*/
        cant_elementos++;
        }

        /* examino un poco el VA a ver que tiene*/
        /*VA_get_i(a,0,(void*)miDiccionario);
        printf("%d\n",TDiccionario_sizeDato(miDiccionario,"user_screen_name"));
        VA_get_i(a,4,(void*)miDiccionario);
        printf("%d\n",TDiccionario_sizeDato(miDiccionario,"user_screen_name"));*/
        /*printf("%d",cant_elementos);*/
        VA_sort(&a,comparar_strings);
        printf("%d",cant_elementos);
        for(i=0;i<cant_elementos;i++)
        {
            VA_get_i(a,i,(void*)miDiccionario);
            sizeDato=TDiccionario_sizeDato(miDiccionario,"user_screen_name");
            buffer=(char *)malloc(sizeDato);
            TDiccionario_obtener(miDiccionario,"user_screen_name",buffer);
            printf("%s\n",buffer);
            free(buffer);
            Tdiccionario_Destruir(miDiccionario);
        }


    free(miDiccionario);
    VA_destroy(&a);
    fclose(archivo);
    Tconstructor_Destruir(&miConstructor);
    TParser_destruir(&miParser);

    return 0;

}

