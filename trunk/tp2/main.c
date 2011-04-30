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
    funccmp fcomp;
    TParser miParser;
    FILE *  archivo;
    char    c;
    int    error=E_NONE,sizeDato;
    char * buffer;
/*    int i;*/  /*aca empiezan las variables del array, por las dudas las separo*/
  /*  int elem;*/


    /*Inicializo el constructor con su cola*/
    Tconstructor_Crear(&miConstructor);
    C_Crear(&colaTweets,sizeof(TDiccionario));
    Tconstructor_setCola(&miConstructor,&colaTweets);
    TParser_Crear(&miParser);

    archivo=fopen(argv[1],"r");

    if(archivo==NULL)
    {
        printf("No puedo abrir el archivo\n");
        return -1;
    }

 c=getc(archivo);

    while( (c!=EOF) && (error==E_NONE) )
    {   printf("%c",c);
        error=TParser_PushChar(&miParser,c);
        c=getc(archivo);
    }

    while ( !C_Vacia(colaTweets)) {
        C_Sacar(&colaTweets,&miDiccionario);

    /*esto es un test para ver que estoy sacando de la cola*/
    sizeDato=TDiccionario_sizeDato(miDiccionario,"id_str");
    if(sizeDato>0)
    {
    buffer=(char *)malloc(sizeDato+1);
    TDiccionario_obtener(miDiccionario,"id_str",buffer);
    printf("%s\n",buffer);
    free(buffer);
    Tdiccionario_Destruir(miDiccionario);
    }
    /*fin test*/
    }


    fclose(archivo);


/*mientas haya datos en la cola,los saco y meto en el array*/
/*    while ( !C_Vacia(colaTweets)) {
        C_Sacar(&colaTweets,&miDiccionario);
        Tdiccionario_Destruir(miDiccionario);
        free(miDiccionario);

    }
    /*
    VA_create(&a, sizeof(int));

    while ( !C_Vacia(&miConstructor.colaDestino)) { /*mientas haya datos en la cola,los saco y meto en el array
        C_Sacar(&miConstructor.colaDestino,&miConstructor.buffer_dict); /*me esta tirando un error con los "->"
        VA_add(&a, &miConstructor.buffer_dict);
    else
        VA_sort(&a, fcomp);
    }

    */




    /*Tdiccionario_Destruir(&miDiccionario);*/

   return 0;

}
