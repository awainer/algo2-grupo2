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
int agregar(char * archname, TParser * miParser, TIndice * idx,TCola * cola)
{
    char c;
    /*TCola cola;*/
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

 typedef enum { AGREGAR, AND, OR, ELIMINART, ELIMINARU, SALIR} T_COMANDO;


int main(int argc, char * argv[])
{


    /*TDiccionario * miDiccionario=NULL;*/
    TCola colaTweets;
    Tconstructor miConstructor;
    TParser     miParser;
    TTokenizer  miTokenizer;
    TIndice     miIndice;
    Tbuscador   miBuscador;
    TDiccionario buffer_dict;

   /* FILE *  archivo;*/
   /* char    c;*/
    int    i=0,j,k=0,s;

    char    comando[STRING_LEN];
    TListaSimple    resultados;
    int     comandos_registrados=0;
    char * comandos[5];
    char * txt_resultado_busqueda;
    char   * buffer_comandos[20];
/*    char   nombre_archivo[255];*/
    char    frase[STRING_LEN];
/*    tweet_id   buffer_res_tid;*/



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
    comandos[SALIR]="salir";
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



    while(strcmp(comando,"salir")!=0)
    {
     buffer_comandos[0]=0;
     printf("-->");
     gets(comando);
     i=0;
        buffer_comandos[i]=strtok(comando," ");
     while (buffer_comandos[i])
     {
        /* printf("%s\n",buffer_comandos[i]);*/
         i++;
         buffer_comandos[i]=strtok(NULL," ");
     }
     frase[0]=0;
     k=0;
     for(j=1;j<i;j++)
     {
         strcat(frase,buffer_comandos[j]);
         strcat(frase," ");
     }
     strcat(frase,"\0");

     buffer_comandos[j+1]=0;
     i=0;

     if(buffer_comandos[0])
     {


      while( (comandos[i]) && (strcmp( buffer_comandos[0],comandos[i] )) )
                i++;

                /*L_Vaciar(&resultados);*/
                switch(i)
                {
                    case AGREGAR :  agregar(buffer_comandos[1],&miParser,&miIndice,&colaTweets);
                                    break;
                    case OR    :    L_Crear(&resultados,sizeof(TDiccionario));
                                    Tbuscador_union(&miBuscador,frase,&resultados);
                                    if(!L_Vacia(resultados))
                                    {   L_Mover_Cte(&resultados,L_Primero);
                                        do{
                                            L_Elem_Cte(resultados,&buffer_dict);
                                            s=TDiccionario_sizeDato(&buffer_dict,"text");
                                            txt_resultado_busqueda=(char*)malloc(s);
                                            TDiccionario_obtener(&buffer_dict,"text",txt_resultado_busqueda);
                                            printf("%s\n",txt_resultado_busqueda);
                                        }while(L_Mover_Cte(&resultados,L_Siguiente));

                                    }
                                    else
                                    {
                                        printf("Sin resultados\n");
                                    }
                                    L_Destruir(&resultados);
                                    break;

                    case AND     :  L_Crear(&resultados,sizeof(TDiccionario));
                                    Tbuscador_interseccion(&miBuscador,frase,&resultados);
                                    if(!L_Vacia(resultados))
                                    {   L_Mover_Cte(&resultados,L_Primero);
                                        do{
                                            L_Elem_Cte(resultados,&buffer_dict);
                                            s=TDiccionario_sizeDato(&buffer_dict,"text");
                                            txt_resultado_busqueda=(char*)malloc(s);
                                            TDiccionario_obtener(&buffer_dict,"text",txt_resultado_busqueda);
                                            printf("%s\n",txt_resultado_busqueda);
                                        }while(L_Mover_Cte(&resultados,L_Siguiente));

                                    }
                                    else
                                    {
                                        printf("Sin resultados\n");
                                    }
                                    L_Destruir(&resultados);
                                    break;



                    case ELIMINART : buffer_comandos[0]=strtok(frase,",");
                                     buffer_comandos[1]=strtok(NULL,",");
                                     /*buffer_comandos[2]=strtok(NULL,",");*/
                                    printf("Elimito el tweet del usuario %s y fecha %s\n",buffer_comandos[0],buffer_comandos[1]);
                                    TIndice_eliminarTweet(&miIndice,buffer_comandos[0],buffer_comandos[1]);
                                    buffer_comandos[0]=0; buffer_comandos[1]=0;
                                    break;
                    case ELIMINARU :
                                    printf("Elimito los tweets de  %s\n",buffer_comandos[1]);
                                    TIndice_eliminarUsuario(&miIndice,buffer_comandos[1]);
                                    break;

                    case SALIR : break;
                    default :   printf("Comando no reconocido\n");
                                break;

                }
     } /*hubo comandos*/


     /*codigo para debug*/
     /*   {
            TNodo_Termino tnt;
            strcpy(tnt.clave,"rugby");
            ABO_Obtener(&miIndice.terminos,&tnt);
            L_Mover_Cte(&tnt.dato,L_Primero);
            do{
                L_Elem_Cte(tnt.dato,&buffer_res_tid);
                printf(" res %s %s\n",buffer_res_tid.date, buffer_res_tid.user);


            }while(L_Mover_Cte(&tnt.dato,L_Siguiente));
        }
*/
     /*fin codigo para debug */
    }/*fin while*/
    L_Vaciar(&resultados);
    L_Destruir(&resultados);
   return 0;
    }

   /* agregar("test.json",&miParser,&miIndice,&colaTweets);
    TIndice_eliminarTweet(&miIndice,"sta","sasas");*/
    /*TIndice_destruir(&miIndice);*/
    /*TIndice_eliminarTweet(&miIndice,"sarasa","asasasa");*/





