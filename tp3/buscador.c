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
    int check;
    char *fraseAux, *pDoc;

    docs = &docsAux;
    L_Crear(&terminos, sizeof(char*));
    Ttokenizer_analizar(tb->tk, frase, &terminos);

    L_Mover_Cte(&terminos, L_Primero);
    L_Elem_Cte(terminos, fraseAux);

    while(!(fraseAux==NULL)){
        check = TIndice_listarDocs(tb->ti, fraseAux, &docsAux);
        if (!(check == FALSE)){
            L_Mover_Cte(&terminos, L_Siguiente);
            L_Elem_Cte(terminos,fraseAux);
        }else {
            L_Mover_Cte(&docsAux, L_Primero);
            L_Elem_Cte(docsAux, pDoc);
            /* Como no se cumplen con TODAS las palabras de la frase, vacio la lista docs */
            while (!(pDoc==NULL)){
                L_Borrar_Cte(&docsAux);
                L_Mover_Cte(&docsAux, L_Siguiente);
                L_Elem_Cte(docsAux, pDoc);
            }
            return 0;
            }
    }

    L_Destruir(&terminos);
    return 0;
}
