#include "buscador.h"
#include "indice.h"
int Tbuscador_crear(Tbuscador* tb, TTokenizer* tt, TIndice* ti)
{
    Ttokenizer_crear(tt);
    tb->tk=tt;
    tb->ti=ti;

    return 0;
}

int Tbuscador_destruir(Tbuscador* tb)
{
    Ttokenizer_destruir(tb->tk);
    return 0;
}

int Tbuscador_union(Tbuscador* tb, char* frase, TListaSimple * docs)
{
    TListaSimple terminos;
    char* fraseAux;

    L_Crear(&terminos, sizeof(char*));


    Ttokenizer_analizar(tb->tk, frase, &terminos);

    L_Mover_Cte(&terminos, L_Primero);
    L_Elem_Cte(terminos, fraseAux);

    while(!(fraseAux==NULL)){
        TIndice_listarDocs(tb->ti, fraseAux, docs);
        L_Mover_Cte(&terminos, L_Siguiente);
        L_Elem_Cte(terminos,fraseAux);
    }

    L_Destruir(&terminos);
    return 0;
}

int Tbuscador_interseccion(Tbuscador* tb, char* frase, TListaSimple * docs)
{
    TListaSimple terminos, docsAux;
    char *fraseAux, *pDoc;

    L_Crear(&terminos, sizeof(char*));
    Ttokenizer_analizar(tb->tk, frase, &terminos);

    L_Mover_Cte(&terminos, L_Primero);
    L_Elem_Cte(terminos, fraseAux);

    while(!(fraseAux==NULL)){
        TIndice_listarDocs(tb->ti, fraseAux, docs);
        L_Mover_Cte(docs, L_Siguiente);
        L_Elem_Cte(docsAux, pDoc);
        if (!(pDoc==NULL)){
            L_Mover_Cte(&terminos, L_Siguiente);
            L_Elem_Cte(terminos,fraseAux);
        }else if (pDoc==NULL){
            L_Mover_Cte(docs, L_Primero);
            L_Elem_Cte(docsAux, pDoc);
            /* Como no se cumplen con TODAS las palabras de la frase, vacio la lista docs */
            while (!(pDoc==NULL)){
                L_Borrar_Cte(&docsAux);
                L_Mover_Cte(docs, L_Siguiente);
                L_Elem_Cte(docsAux, pDoc);
            }
            }
    }
    L_Destruir(&terminos);
    return 0;
}
