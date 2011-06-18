#include "buscador.h"
#include "indice.h"
int Tbuscador_crear(Tbuscador* tb, TTokenizer* tt, TIndice* ti)
{

    tb->tk=tt;
    tb->ti=ti;

    return 0;
}

int Tbuscador_destruir(Tbuscador* tb)
{

    return 0;
}

int Tbuscador_union(Tbuscador* tb, char* frase, TListaSimple * docs)
{
    TListaSimple    terminos;
    char fraseAux[STRING_LEN];

    /*Creo lista donde se van a cargar las frases tokenizadas */
    L_Crear(&terminos, STRING_LEN);

    Ttokenizer_analizar(tb->tk, frase, &terminos);

    if ((L_Vacia(terminos))){
                return 0;
    }

     L_Mover_Cte(&terminos, L_Primero);
     do{
      L_Elem_Cte(terminos, fraseAux);
      TIndice_listarDocs(tb->ti, fraseAux, docs);
       } while (L_Mover_Cte(&terminos,L_Siguiente));
       /* while(!(fraseAux==NULL)){
         /*   TIndice_listarDocs(tb->ti, fraseAux, docs);
            L_Mover_Cte(&terminos, L_Siguiente);
            L_Elem_Cte(terminos,fraseAux);
        }*/



    L_Destruir(&terminos);

    return 0;
}

int Tbuscador_interseccion(Tbuscador* tb, char* frase, TListaSimple * docs)
{
    TListaSimple terminos;
    int check;
    char *fraseAux;

    L_Crear(&terminos, sizeof(char*));
    Ttokenizer_analizar(tb->tk, frase, &terminos);

    L_Mover_Cte(&terminos, L_Primero);
    L_Elem_Cte(terminos, fraseAux);

    while(!(fraseAux==NULL)){
        /*Si existen terminos, se cargan en la lista docs. Sino, vacio la lista ya que no cumple con alguna palabra y salgo de la primitiva. */
        check = TIndice_listarDocs(tb->ti, fraseAux, docs);
        if (check == TRUE){
            L_Mover_Cte(&terminos, L_Siguiente);
            L_Elem_Cte(terminos,fraseAux);
        }else {
            L_Vaciar(docs);
            /* Como no se cumplen con TODAS las palabras de la frase, vacio la lista docs y salgo de la funcion. */
            return 0;
            }
    }

    L_Destruir(&terminos);
    return 0;
}
