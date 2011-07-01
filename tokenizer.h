#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED

#include "lista.h"

typedef struct _t_tok {
    int numero_separadores;
    char  separadores[10][5];
} TTokenizer;

/*pre: ninguna
post: el TDA Tokenizer fue creado*/

int Ttokenizer_crear(TTokenizer* tt);

/*pre: el TDA Tokenizer fue creado
post: se liberaron recursos del TDA Tokenizer*/
int Ttokenizer_destruir(TTokenizer* tt);
/*pre: el TDA Tokenizer fue creado. Términos es una lista de char*
que contiene los terminos ya analizados.
post: se cargo la lista de terminos pasada como parametro con la
lista de palabras contenidas en la frase. Estas palabras fueron
procesadas según el alumno definio.*/

int Ttokenizer_analizar(TTokenizer* tt, char* frase, TListaSimple * terminos);




#endif
