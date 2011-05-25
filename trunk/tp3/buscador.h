#ifndef BUSCADOR_H_INCLUDED
#define BUSCADOR_H_INCLUDED

#include "tokenizer.h"
#include "indice.h"
#include "lista.h"

/**TDA Buscador (Tbuscador)**/
typedef struct{
    TTokenizer * tk;
    TIndice    * ti;
}Tbuscador;


/*pre: ninguna
post: el TDA Buscador ha sido creado. Tt es un puntero al
tokenizer que se usará para analizar los strings de búsqueda*/
int Tbuscador_crear(Tbuscador* tb, TTokenizer* tt, TIndice* ti);
/*pre: el TDA Buscador ha sido creado
post: los recursos del Buscador fueron liberados*/
int Tbuscador_destruir(Tbuscador* tb);
/*pre: el TDA Buscador ha sido creado. Docs es una lista de
Tdiccionarios* que va a contener los Tweets
post: se devuelve el conjunto de documentos que cumple con alguna
de las palabras de la frase. La frase es tokenizada previamente
mediante el TDA tokenizer. Los Tweets resultado se devuelven en la
lista docs.*/
int Tbuscador_union(Tbuscador* tb, char* frase, TListaSimple * docs);
/*pre: el TDA Buscador ha sido creado. Docs es una lista de
TDiccionario* que va a tener los Tweets
post: se devuelve el conjunto de documentos que cumple con todas
de las palabras de la frase. La frase es tokenizada previamente
mediante el TDA tokenizer. Los Tweets resultado se devuelven en la
lista docs.*/
int Tbuscador_interseccion(Tbuscador* tb, char* frase, TListaSimple * docs);


#endif
