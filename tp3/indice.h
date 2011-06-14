#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include "ABO.h"
#include "tokenizer.h"
#include "dict.h"
#include "lista.h"

#define STRING_LEN 255

typedef struct{
    char  user[STRING_LEN];
    char  date[STRING_LEN];
}tweet_id;

typedef struct {
    char  clave[STRING_LEN];
    TListaSimple dato;
}TNodo_Termino;

typedef struct {
    tweet_id  clave;
    TDiccionario  valor;
}TNodo_Tweet;

typedef struct TIndice{
    TTokenizer * tk;
    TABO terminos;
    TABO tweets;

}TIndice;

/*pre: ninguna
post: el índice fue creado, estableciendo como tokenizer que será
usado al agregar Tweets a ta*/
int TIndice_crear(TIndice* ti, TTokenizer* ta);
/*pre: el índice fue creado
post: los recursos del índice fueron liberados*/
int TIndice_destruir(TIndice* ti);
/*pre: el índice fue creado
post: se agregó un nuevo Tweet al índice El texto indexado es el
que esta en el campo “text” del Tweet*/
int TIndice_agregar(TIndice* ti, TDiccionario* Tweet);
/*pre: el índice fue creado. Docs es una lista de TDiccionario* que
se cargará con Tweets.
post: carga en la lista “docs” pasada como parámetro, los punteros
a TDiccionario que contienen el término. Si el termino no se
encuentra en el índice, la lista se deja vacía.*/
int TIndice_listarDocs(TIndice* ti, char* termino, TListaSimple * docs);
/*pre: el índice fue creado
post: elimina el Tweet identificado por el usuario y fecha pasados
como parámetros.*/
int TIndice_eliminarTweet(TIndice* ti, char* usuario, char* fecha);
/*pre: el índice fue creado
post: elimina todos los Tweets del usuario pasado como parámetro.*/
int TIndice_eliminarUsuario(TIndice* ti, char* usuario);
/*pre: el índice fue creado
post: Reconstruye el índice haciendo más eficiente la búsqueda.
Los Tweets que contiene después de optimizar deben ser los mismos
que antes de optimizar. Ver notas de implementación.*/
int TIndice_optimizar(TIndice* ti);


#endif
