#include "indice.h"
#include <stdio.h>

int TIndice_crear(TIndice* ti, TTokenizer* ta)
{
    AB_Crear(&ti->terminos,sizeof(TNodo_Termino));
    AB_Crear(&ti->tweets,sizeof(TNodo_Tweet));
    ti->tk=ta;
    return 0;
}
/*pre: el índice fue creado
post: los recursos del índice fueron liberados*/
int TIndice_destruir(TIndice* ti)
{
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
    TDiccionario aux_dict;
    TNodo_Termino aux_nodo_termino;
    TNodo_Tweet   aux_nodo_tweet;
    TListaSimple  lista_terminos;
    int s=0;
    /*tweet_id   id;*/
    char *   texto;


    /* Esto tal vez deberia ir en algun constructor*/
    TDiccionaro_Crear(&aux_nodo_tweet.valor);
    /*aux_nodo_tweet.clave=NULL;*/

    obtener_id(Tweet,aux_nodo_tweet.clave);

    s=TDiccionario_sizeDato(Tweet,"text");
    texto=malloc(s);
    TDiccionario_obtener(Tweet,"text",texto);

    Ttokenizer_analizar(ti->tk,texto,&lista_terminos);

    if(AB_Vacio(ti->tweets)) /*tal vez deberiamos chequear que ambos arboles esten vacios...*/
    {
  /*    AB_MoverCte(ti->tweets,RAIZ);
        AB_Insertar()
        AB_MoverCte(ti->terminos,RAIZ);*/

    }

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
