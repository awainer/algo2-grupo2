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
int agregar(char * archname, TParser * miParser, TIndice * idx)
{
    char c;
    TCola cola;
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


    while ( !C_Vacia(cola)) {
        C_Sacar(&cola,&aux_dict);
        TIndice_agregar(idx,&aux_dict);
    }
    return error;
}
 typedef enum { AGREGAR, AND, OR, ELIMINART, ELIMINARU} T_COMANDO;


int main(int argc, char * argv[])
{


    TDiccionario * miDiccionario=NULL;
    TCola colaTweets;
    Tconstructor miConstructor;
    TParser     miParser;
    TTokenizer  miTokenizer;
    TIndice     miIndice;
    Tbuscador   miBuscador;

    FILE *  archivo;
    char    c;
    int    error=E_NONE,sizeDato,i=0;

    char    comando[STRING_LEN];
    TListaSimple    args;
    int     fincom,comandos_registrados=0;
    char * comandos[5];
    char   nombre_archivo[255];


    comandos[AGREGAR]="agregar";
    comandos_registrados++;
    comandos[AND]="and";
    comandos_registrados++;
    comandos[OR]="or";
    comandos_registrados++;
    comandos[ELIMINART]="eliminart";
    comandos_registrados++;
    comandos[ELIMINARU]="eliminaru";
    comandos_registrados++;

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

    L_Crear(&args,STRING_LEN);
    while(strcmp(comando,"salir")!=0)
    {
     printf("-->\n");
     gets(comando);

     Ttokenizer_analizar(&miTokenizer,comando,&args);
     if(!L_Vacia(args))
     {
         L_Mover_Cte(&args,L_Primero);
         L_Elem_Cte(args,&comando);
         printf("%s\n",comando);
         /* aca va la magia */
        i=0;
        while( (strcmp( comando,comandos[i] )) && (i < comandos_registrados) )
            i++;

                switch(i)
                {
                    case AGREGAR :  L_Mover_Cte(&args,L_Siguiente);
                                    L_Elem_Cte(args,nombre_archivo);
                                    agregar(nombre_archivo,&miParser,&miIndice);
                                    break;
                    case AND    :   break;
                    case OR     :   break;
                    case ELIMINART : break;
                    case ELIMINARU : break;
                    default :   printf("Comando no reconocido\n");
                                break;
                }


        printf("%d\n",i);
         L_Vaciar(&args);
     }

    }

   /* agregar("test.json",&miParser,&miIndice,&colaTweets);
    TIndice_eliminarTweet(&miIndice,"sta","sasas");*/
    /*TIndice_destruir(&miIndice);*/
    /*TIndice_eliminarTweet(&miIndice,"sarasa","asasasa");*/

   return 0;

}

