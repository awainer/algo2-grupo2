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
{
        /*Esto tiene que recorrer los dos arboles recursivamente e ir destruyendo todo*/
        return 0;
}


void obtener_id(TDiccionario* tw,tweet_id * id)
{
    int s;


    s=TDiccionario_sizeDato(tw,"user_screen_name");
 /*   id->user=(char*)malloc(s);*/
    TDiccionario_obtener(tw,"user_screen_name",id->user);
    s=TDiccionario_sizeDato(tw,"created_at");
    /*id->date=(char*)malloc(s);*/
    TDiccionario_obtener(tw,"created_at",id->date);
    printf("%s , %s\n",id->user,id->date);
}

/*pre: el índice fue creado
post: se agregó un nuevo Tweet al índice El texto indexado es el
que esta en el campo “text” del Tweet*/
int TIndice_agregar(TIndice* ti, TDiccionario* Tweet)
{
/*    TDiccionario aux_dict;
    TNodo_Termino aux_nodo_termino;*/
    TNodo_Tweet   aux_nodo_tweet;
    TListaSimple  lista_terminos;
    int s=0;
    /*tweet_id   id;*/
    char *   texto;


    /* Esto tal vez deberia ir en algun constructor*/
    /*TDiccionaro_Crear(&aux_nodo_tweet.valor);*/
    /*aux_nodo_tweet.clave=NULL;*/
    /*cargo el nodo tweet y lo inserto*/
    obtener_id(Tweet,&aux_nodo_tweet.clave);
    aux_nodo_tweet.valor=Tweet;
    ABO_Insertar(&ti->tweets,&aux_nodo_tweet);

    s=TDiccionario_sizeDato(Tweet,"text");
    texto=malloc(s);
    TDiccionario_obtener(Tweet,"text",texto);
    L_Crear(&lista_terminos,sizeof(char*));
    Ttokenizer_analizar(ti->tk,texto,&lista_terminos);

    /*ACA hay que agregar codigo que busque si un termino esta, en ese caso agregue el tweet_id*/

    L_Destruir(&lista_terminos);

    free(texto);
    return 0;
}
/*pre: el índice fue creado. Docs es una lista de TDiccionario* que
se cargará con Tweets.
post: carga en la lista “docs” pasada como parámetro, los punteros
a TDiccionario que contienen el término. Si el termino no se
encuentra en el índice, la lista se deja vacía.*/
int TIndice_listarDocs(TIndice* ti, char* termino, TListaSimple * docs)
{

    return 0;
}
/*pre: el índice fue creado
post: elimina el Tweet identificado por el usuario y fecha pasados
como parámetros.*/
int TIndice_eliminarTweet(TIndice* ti, char* usuario, char* fecha)
{
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
