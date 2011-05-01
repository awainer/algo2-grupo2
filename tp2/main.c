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
/*    V_Array a;
    funccmp fcomp;*/
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
    while ( !C_Vacia(colaTweets)) {
        miDiccionario=(TDiccionario*)malloc(sizeof(TDiccionario));
        TDiccionaro_Crear(miDiccionario);
        C_Sacar(&colaTweets,miDiccionario);
        sizeDato=TDiccionario_sizeDato(miDiccionario,"user_screen_name");
        printf("%d\n",sizeDato);
        buffer=(char *)malloc(sizeDato);
        TDiccionario_obtener(miDiccionario,"user_screen_name",buffer);
        printf("%s\n",buffer);
        Tdiccionario_Destruir(miDiccionario);
        free(miDiccionario);
        free(buffer);
    }
    /*esto es un test para ver que estoy sacando de la cola*/
    /*sizeDato=TDiccionario_sizeDato(miDiccionario,"id_str");
    if(sizeDato>0)
    {
    buffer=(char *)malloc(sizeDato+1);
    TDiccionario_obtener(miDiccionario,"id_str",buffer);
    printf("%s\n",buffer);
    free(buffer);
    Tdiccionario_Destruir(miDiccionario);
    }
    /*fin test*/
    /*}*/


    fclose(archivo);




/*    VA_create(&a, sizeof(int));*/

    /*while ( !C_Vacia(colaTweets)) {
        C_Sacar(&colaTweets,&miDiccionario);
        sizeDato=TDiccionario_sizeDato(miDiccionario,"user_screen_name"); /* creo que es user_dato */
        /*if( sizeDato>0 ) {
        buffer=(char*)malloc(sizeDato);
        TDiccionario_obtener(miDiccionario,"user_screen_name",buffer);
        free(buffer);
        }*/
   /*     VA_add(&a,buffer );*/
       /* Tdiccionario_Destruir(miDiccionario);
        free(miDiccionario);
    }*/

     /*  if (!C_Vacia(colaTweets)){
        VA_sort(&a, fcomp); /* revisar como funciona este fcomp */
       /* }*/


/* a partir de aca el array deberia estar con datos y ordenado */
/*int cant_elem_VArray = VA_count (a), recorredor_VArray = 0, contador_tweets_usuario;
char* elemento_actual, elemento_anterior;

while ( recorredor_VArray < cant_elem_VArray ){

	VA_get_i(a,recorredor_VArray,&elemento_actual);
	if (recorredor_VArray == 0){
            strcpy(&elemento_actual, &elemento_anterior);
			contador_tweets_usuario = 1;
		}
	else if (recorredor_VArray > 0){
		if (!(strcmp(&elemento_actual, &elemento_anterior) == 0)){
			printf("%s : %d\n", elemento_anterior, &contador_tweets_usuario);
			strcpy(&elemento_actual, &elemento_anterior);
			contador_tweets_usuario = 1;
        }
		else
		contador_tweets_usuario++;

	recorredor_VArray++;
}
}


    /*Tdiccionario_Destruir(&miDiccionario);*/

   return 0;

}

