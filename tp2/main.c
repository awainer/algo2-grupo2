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
    char * buffer;
    int sizeDato;
    int borrame;
    TCola colaTweets;
    Tconstructor miConstructor;


    int i; /*aca empiezan las variables del array, por las dudas las separo*/
    int elem;
    funccmp fcomp;
    V_Array a;


    /*Inicializo el constructor con su cola*/
    Tconstructor_Crear(&miConstructor);
    C_Crear(&colaTweets,sizeof(TDiccionario));
    Tconstructor_setCola(&miConstructor,&colaTweets);

    while ( !C_Vacia(colaTweets)) { /*mientas haya datos en la cola,los saco y meto en el array*/
        C_Sacar(&colaTweets,&miDiccionario); /*me esta tirando un error con los "->"*/
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


    /*TDiccionaro_Crear(&miDiccionario);
    TDiccionario_colocar(&miDiccionario,"hola","1234567");
    TDiccionario_colocar(&miDiccionario,"como","estas");
    TDiccionario_colocar(&miDiccionario,"hola","mundoooooooooooooooooooooooo"); /*podemos pisar el valor de algo */
/*    TDiccionario_colocar(&miDiccionario,"color","verde fosforescente");



    /*Asi es como se lee del diccionario */
  /*  sizeDato=TDiccionario_sizeDato(&miDiccionario,"como");
    if(sizeDato>0)
    {
    buffer=(char *)malloc(sizeDato+1);
    TDiccionario_obtener(&miDiccionario,"como",buffer);
    printf("%s\n",buffer);
    free(buffer);
    }
*/


    /*Tdiccionario_Destruir(&miDiccionario);*/


    /*archivo=fopen(argv[1],"r");
    TParser_Crear(&miParser);
   if(archivo==NULL)
    {
        printf("No puedo abrir el archivo\n");
        return -1;
    }




    fclose(archivo);*/
    return 0;

}

