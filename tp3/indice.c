#include "indice.h"
#include <stdio.h>

int comparar_tweet_id(void * v1, void * v2)
{
    tweet_id  *t1,*t2;
    int aux;

    t1=v1;
    t2=v2;
    aux=strcmp(t1->user,t2->user);

    if(aux!=0) return aux;
    else{
        return strcmp(t1->date,t2->date);
        }

    return 0;
}
int comparar_termino(void * v1, void * v2)
{
    return strcmp((char*)v1,(char*)v2);
}

int borrar_tweet(void * t,void * v2)
{
    TNodo_Tweet * aux=t;
    Tdiccionario_Destruir(aux->valor);
    free(t);
    return 0;
}


/*pre: el corriente esta en la raiz*/


int TIndice_crear(TIndice* ti, TTokenizer* ta)
{
    ABO_Crear(&ti->terminos,comparar_termino,sizeof(TNodo_Termino));
    ABO_Crear(&ti->tweets,comparar_tweet_id,sizeof(TNodo_Tweet));
    ti->tk=ta;
    return 0;
}
/*pre: el índice fue creado
post: los recursos del índice fueron liberados*/
int TIndice_destruir(TIndice* ti)
{       ABO_ProcesarInOrden(&ti->tweets,borrar_tweet,NULL);
        /*Esto tiene que recorrer los dos arboles recursivamente e ir destruyendo todo*/
        /*Recorro el arbol de tweets*/

        /*borrar_arbol_tweets()*/
        return 0;
}


void obtener_id(TDiccionario* tw,tweet_id * id)
{
    int s;
    s=TDiccionario_sizeDato(tw,"user_screen_name");
    TDiccionario_obtener(tw,"user_screen_name",id->user);
    s=TDiccionario_sizeDato(tw,"created_at");
    TDiccionario_obtener(tw,"created_at",id->date);
}

/*pre: el índice fue creado
post: se agregó un nuevo Tweet al índice El texto indexado es el
que esta en el campo “text” del Tweet*/
int TIndice_agregar(TIndice* ti, TDiccionario* Tweet)
{
    TNodo_Tweet   aux_nodo_tweet;
    TNodo_Termino aux_nodo_termino;
    TListaSimple  lista_terminos;
    int s=0;
    char *   texto;
    char buffer_termino[255];

    /*cargo el nodo tweet y lo inserto*/
    obtener_id(Tweet,&aux_nodo_tweet.clave);
    aux_nodo_tweet.valor=Tweet;
    ABO_Insertar(&ti->tweets,&aux_nodo_tweet);
    /*ahora empiezo con los terminos*/

    s=TDiccionario_sizeDato(Tweet,"text");
    texto=malloc(s);
    TDiccionario_obtener(Tweet,"text",texto);
    L_Crear(&lista_terminos,sizeof(char*));



    Ttokenizer_analizar(ti->tk,texto,&lista_terminos);
    L_Mover_Cte(&lista_terminos,L_Primero);

    do
    {

        L_Elem_Cte(lista_terminos,&aux_nodo_termino.clave);
        if(!ABO_Obtener(&ti->terminos,aux_nodo_termino.clave))
        {
          /*  printf("termino repetido %s\n",aux_nodo_termino.clave);*/
            L_Insertar_Cte(&aux_nodo_termino.dato,L_Siguiente,&aux_nodo_tweet.clave);
            ABO_Actualizar(&ti->terminos,&aux_nodo_termino);
        }
        else
        {
            /*printf("nuevo termino %s\n",aux_nodo_termino.clave);*/
            /*Preparo el dato que voy a insertar*/
            L_Crear(&aux_nodo_termino.dato,sizeof(tweet_id));
            L_Insertar_Cte(&aux_nodo_termino.dato,L_Siguiente,&aux_nodo_tweet.clave); /*este es el tweet_id del tw que venimos procesando*/
            ABO_Insertar(&ti->terminos,&aux_nodo_termino);
        }

    }while (L_Mover_Cte(&lista_terminos,L_Siguiente));



    L_Destruir(&lista_terminos);

    free(texto);
    return 0;
}


int imprimirIDs(void * v1, void * v2)
{
    tweet_id * aux;
    printf("%s %s\n",aux->date,aux->user);
    return 0;
}
/*pre: el índice fue creado. Docs es una lista de TDiccionario* que
se cargará con Tweets.
post: carga en la lista “docs” pasada como parámetro, los punteros
a TDiccionario que contienen el término. Si el termino no se
encuentra en el índice, la lista se deja vacía.*/
int TIndice_listarDocs(TIndice* ti, char* termino, TListaSimple * docs)
{
    /*aboRecorrer(&ti->tweets,imprimirCOND,RAIZ,NULL);*/

    return 0;
}
/*pre: el índice fue creado
post: elimina el Tweet identificado por el usuario y fecha pasados
como parámetros.*/
int TIndice_eliminarTweet(TIndice* ti, char* usuario, char* fecha)
{
    TNodo_Tweet aux;
    strcpy(aux.clave.date,fecha);
    strcpy(aux.clave.user,usuario);
    /*ABO_*/
    return 0;
}
/*pre: el índice fue creado
post: elimina todos los Tweets del usuario pasado como parámetro.*/
int TIndice_eliminarUsuario(TIndice* ti, char* usuario)
{
    return 0;
}
/*pre: el índice fue creado
post: Reconstruye el índice haciendo más eficiente la búsqueda.
Los Tweets que contiene después de optimizar deben ser los mismos
que antes de optimizar. Ver notas de implementación.*/
int TIndice_optimizar(TIndice* ti)
{
    return 0;
}
