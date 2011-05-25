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
#include "tokenizer.h"
#include "indice.h"
#include "buscador.h"
/*sacar esto, esta para probar algo */
#include <string.h>

/* int main(int argc, char * argv[])
{
   TTokenizer miTokenizer;
    TListaSimple  res;
    char  msg[50];
    char * term;

    Ttokenizer_crear(&miTokenizer);

    L_Crear(&res,sizeof(char*));
    strcpy(msg,"hola mundo  y como, te va  sArAsA!!!");
    Ttokenizer_analizar(&miTokenizer,msg,&res);


    L_Mover_Cte(&res,L_Primero);

    do
    {

        L_Elem_Cte(res,&term);
        printf("%s\n",term);
        free(term);
    }while (L_Mover_Cte(&res,L_Siguiente));
     L_Destruir(&res);
    return 0;
}*/


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

/*Funcion  para parsear un nuevo archivo */
int agregar(char * archname, TParser * miParser, TIndice * idx, TCola * cola)
{
    char c;
    int error=E_NONE;
    FILE * archivo;
    TDiccionario aux_dict;

    archivo=fopen(archname,"r");


    if(archivo==NULL)
    {
        printf("No puedo abrir el archivo\n");
        return -1;
    }

    c=getc(archivo);
    while( (c!=EOF) && (error==E_NONE) )
    {   /*printf("%c",c);*/
        error=TParser_PushChar(miParser,c);
        c=getc(archivo);


    }


    while ( !C_Vacia(*cola)) {
        C_Sacar(cola,&aux_dict);
        TIndice_agregar(idx,&aux_dict);
    }






    return error;
}



int main(int argc, char * argv[])
{


    TDiccionario * miDiccionario=NULL;
    TCola colaTweets;
    Tconstructor miConstructor;
    TParser     miParser;
    TTokenizer  miTokenizer;
    TIndice     miIndice;
    Tbuscador   miBuscador;

    /*TListaOrdenada miListaOrdenada;
    int flag;*/
    FILE *  archivo;
    char    c;
    int    error=E_NONE,sizeDato,i=0;

/*    char * nuevo=NULL, * actual=NULL;*/




    /*Inicializo el constructor con su cola*/

    C_Crear(&colaTweets,sizeof(TDiccionario));
    Tconstructor_Crear(&miConstructor);
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

    /*Inicializo el buscador, indice y tokenizer */

    Ttokenizer_crear(&miTokenizer);
    TIndice_crear(&miIndice,&miTokenizer);
    Tbuscador_crear(&miBuscador,&miTokenizer,&miIndice);

    agregar("test.json",&miParser,&miIndice,&colaTweets);

if(error==E_NONE)
{

    /*Saco de la cola y meto en la lista ordenada*/
/*    miDiccionario=(TDiccionario*)malloc(sizeof(TDiccionario));
    LO_Crear(&miListaOrdenada,sizeof(TDiccionario),comparar_dicts);
    while ( !C_Vacia(colaTweets)) {
        C_Sacar(&colaTweets,miDiccionario);
        LO_Insertar(&miListaOrdenada,miDiccionario);
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
*/
    }
   return 0;

}

