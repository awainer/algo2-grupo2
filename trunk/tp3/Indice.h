#include "dict.h"
#include "lista.h"
#include "AB.h"
#include "tokenizer.h"





typedef struct {

char* Clave;
TListaSimple documentos;

}Def;

typedef struct {

TAB elementos;
TTokenizer tnizer;
TDiccionario Tweet;

}Tindice





/*pre: ninguna
post: el índice fue creado, estableciendo como tokenizer que será
usado al agregar Tweets a ta*/
Tindice_crear(Tindice* ti, Ttokenizer* ta)

/*pre: el índice fue creado
post: los recursos del índice fueron liberados*/
TIndice_destruir(Tindice* ti)

/*pre: el índice fue creado
post: se agregó un nuevo Tweet al índice El texto indexado es el
que esta en el campo “text” del Tweet*/
TIndice_agregar(Tindice* ti, TDiccionario* Tweet)

/*pre: el índice fue creado. Docs es una lista de TDiccionario* que
se cargará con Tweets.
post: carga en la lista “docs” pasada como parámetro, los punteros
a TDiccionario que contienen el término. Si el termino no se
encuentra en el índice, la lista se deja vacía.*/
TIndice_listarDocs(Tindice* ti, char* termino, TLista * docs)

/*pre: el índice fue creado
post: elimina el Tweet identificado por el usuario y fecha pasados
como parámetros.*/
TIndice_eliminarTweet(Tindice* ti, char* usuario, char* fecha)

/*pre: el índice fue creado
post: elimina todos los Tweets del usuario pasado como parámetro.*/
TIndice_eliminarUsuario(Tindice* ti, char* usuario)

/*pre: el índice fue creado
post: Reconstruye el índice haciendo más eficiente la búsqueda.
Los Tweets que contiene después de optimizar deben ser los mismos
que antes de optimizar. Ver notas de implementación.*/
TIndice_optimizar(Tindice* ti)
