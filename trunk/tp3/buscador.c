#include "buscador.h"

int Tbuscador_crear(Tbuscador* tb, TTokenizer* tt, TIndice* ti)
{
    Ttokenizer_crear(tt);
    tb->tk=tt;
    tb->ti=ti;

    return 0;
}

int Tbuscador_destruir(Tbuscador* tb)
{
    Ttokenizer_destruir(&tb->tk);
    return 0;
}

int Tbuscador_union(Tbuscador* tb, char* frase, TListaSimple * docs)
{
    TListaSimple *terminosAux; /* Puntero donde se cargaran  los punteros TDiccionario que contengan el término. */
    TListaSimple tAux;
    terminosAux = (TListaSimple*) malloc(sizeof(TListaSimple));

    char * fraseAux;

    Ttokenizer_analizar(&tb->tk, frase, terminosAux);

    L_Mover_Cte(&terminosAux, L_Primero);
    L_Elem_Cte(tAux, fraseAux);

    while(!(fraseAux==NULL)){
        Tindice_listarDocs(&tb->ti, fraseAux, docs);
        L_Mover_Cte(&terminosAux, L_Siguiente);
        L_Elem_Cte(tAux,fraseAux);
    }

    free(terminosAux);

    return 0;
}

int Tbuscador_interseccion(Tbuscador* tb, char* frase, TListaSimple * docs)
{
    TListaSimple* terminosAux; /* Puntero donde se cargaran  los punteros TDiccionario que contengan el término. */
    TListaSimple tAux;
    terminosAux = (TListaSimple*) malloc(sizeof(TListaSimple));
    char * fraseAux;

    Ttokenizer_analizar(&tb->tk, frase, terminosAux);

    L_Mover_Cte(&terminosAux, L_Primero);
    L_Elem_Cte(tAux, fraseAux);

    while(!(fraseAux==NULL)){
        Tindice_listarDocs(&tb->ti, fraseAux, docs);
        if (!((L_Mover_Cte(&docs, L_Siguiente)==NULL))){
            L_Mover_Cte(&terminosAux, L_Siguiente);
            L_Elem_Cte(tAux,fraseAux);
        }else if ((L_Mover_Cte(&docs, L_Siguiente))==NULL){
            L_Mover_Cte(&docs, L_Primero);
            /* Como no se cumplen con TODAS las palabras de la frase, vacio la lista docs */
            while (!(L_Mover_Cte(&docs, L_Siguiente)==NULL))
                L_Borrar_Cte(&docs);
            }
    }
    free(terminosAux);
    return 0;
}
