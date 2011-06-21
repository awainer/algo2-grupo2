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

     L_Destruir(&terminos);

    return 0;
}

/*void ls_interseccion(TListaSimple * l1, TListaSimple * l2, TListaSimple * dest, int (*fcmp)(void*,void*),int tam)
{
    int f=TRUE;
    L_Mover_Cte(l1,L_Primero);
    do{
        do{



        }

    }while(L_Mover_Cte(l1,L_Siguiente))

}*/

int contiene(TDiccionario d, TListaSimple ls, TTokenizer * tk)
{
    int s;
    char * text;
    TListaSimple tokens;
    int cont=FALSE;
    char  aux1[STRING_LEN],aux2[STRING_LEN];

    s = TDiccionario_sizeDato(&d,"text");
    text = (char*) malloc(s);
    TDiccionario_obtener(&d,"text",text);
    L_Crear(&tokens,sizeof(char[STRING_LEN]));
    Ttokenizer_analizar(tk,text,&tokens);

    L_Mover_Cte(&ls,L_Primero);
    do {
        L_Elem_Cte(ls,aux1);
        L_Mover_Cte(&tokens,L_Primero);

        do{
            L_Elem_Cte(tokens,aux2);
            if(!strcmp(aux1,aux2))
                cont=TRUE;
        } while ((L_Mover_Cte(&tokens,L_Siguiente)) && (!cont) );


    }while((L_Mover_Cte(&ls,L_Siguiente)) &&  (!cont) );

    return cont;
}

int Tbuscador_interseccion(Tbuscador* tb, char* frase, TListaSimple * docs)
{
    TListaSimple    terminos;
    char fraseAux[STRING_LEN];
    TDiccionario    dict_aux;
    /*Creo lista donde se van a cargar las frases tokenizadas */
    L_Crear(&terminos, sizeof(char[STRING_LEN]));

    Ttokenizer_analizar(tb->tk, frase, &terminos);

    if ((L_Vacia(terminos))){
                return 0;
    }

     L_Mover_Cte(&terminos, L_Primero);
     do{
            L_Elem_Cte(terminos, fraseAux);
            TIndice_listarDocs(tb->ti, fraseAux, docs);
       } while (L_Mover_Cte(&terminos,L_Siguiente));


     L_Mover_Cte(docs, L_Primero);
     do {
            L_Elem_Cte(*docs,&dict_aux);

            if(!contiene(dict_aux,terminos,tb->tk ))
                L_Borrar_Cte(docs);

       }while( L_Mover_Cte(docs, L_Siguiente));


    L_Destruir(&terminos);
    return 0;
}
