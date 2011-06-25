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

int comparar_dicts(void* v1, void* v2)
{
 TDiccionario *d1,*d2;
    int aux;
    char * buffer1, * buffer2;

    d1=(TDiccionario*)v1;
    d2=(TDiccionario*)v2;

    aux=TDiccionario_sizeDato(d1,"user_screen_name");
    buffer1=(char*)malloc(aux);
    TDiccionario_obtener(d1,"user_screen_name",buffer1);
    aux=TDiccionario_sizeDato(d2,"user_screen_name");
    buffer2=(char*)malloc(aux);
    TDiccionario_obtener(d2,"user_screen_name",buffer2);
    aux=strcmp(buffer1,buffer2);
    free(buffer1);
    free(buffer2);
    return aux;

}

int contiene(TDiccionario d, TListaSimple ls, TTokenizer * tk)
{
    int s;
    char * text;
    TListaSimple tokens;
/*    int cont=FALSE;*/
    char  aux1[STRING_LEN],aux2[STRING_LEN];
    int cant_tokens=0,tokens_encontrados=0;

    s = TDiccionario_sizeDato(&d,"text");
    text = (char*) malloc(s);
    TDiccionario_obtener(&d,"text",text);
    L_Crear(&tokens,sizeof(char[STRING_LEN]));
    Ttokenizer_analizar(tk,text,&tokens);

    L_Mover_Cte(&ls,L_Primero);

    do{ cant_tokens++;} while(L_Mover_Cte(&ls,L_Siguiente));


    /*aux1 son los tokens que busco, aux2 son los tokens del string tokenizado*/
    L_Mover_Cte(&ls,L_Primero);
    L_Mover_Cte(&tokens,L_Primero);
    do {
        L_Elem_Cte(ls,aux1);

        do{
            L_Elem_Cte(tokens,aux2);
            /*if((strcmp(aux1,aux2)==0) && (!L_Mover_Cte(&ls,L_Siguiente)))*/
            if((strcmp(aux1,aux2)==0))
                tokens_encontrados++;
        } while ((L_Mover_Cte(&tokens,L_Siguiente)) );
    }while(L_Mover_Cte(&ls,L_Siguiente));
/*        } while ((L_Mover_Cte(&tokens,L_Siguiente)) && (tokens_encontrados<cant_tokens) );
    }while(L_Mover_Cte(&ls,L_Siguiente) &&  (tokens_encontrados<cant_tokens) );*/

   /* printf("TKS: %d, %s\n",tokens_encontrados,text);*/

    free(text);
    L_Destruir(&tokens);

    if(cant_tokens<=tokens_encontrados)
        return TRUE;
    else
        return FALSE;

}

int Tbuscador_interseccion(Tbuscador* tb, char* frase, TListaSimple * docs)
{
    TListaSimple    terminos,ls_aux;
    char fraseAux[STRING_LEN];
    TDiccionario    dict_aux;
    /*Creo lista donde se van a cargar las frases tokenizadas */
    L_Crear(&terminos, sizeof(char[STRING_LEN]));
    L_Crear(&ls_aux, sizeof(TDiccionario));
    Ttokenizer_analizar(tb->tk, frase, &terminos);

    if ((L_Vacia(terminos))){
                return 0;
    }

     L_Mover_Cte(&terminos, L_Primero);
     do{
            L_Elem_Cte(terminos, fraseAux);
            TIndice_listarDocs(tb->ti, fraseAux, &ls_aux);
       } while (L_Mover_Cte(&terminos,L_Siguiente));

    if (L_Vacia(ls_aux)){
                return 0;
    }


     L_Mover_Cte(&ls_aux, L_Primero);
     do {
            L_Elem_Cte(ls_aux,&dict_aux);

            if(contiene(dict_aux,terminos,tb->tk ))
                L_Insertar_Cte(docs,L_Siguiente,&dict_aux);
                /*L_Borrar_Cte(docs);*/

       }while( L_Mover_Cte(&ls_aux, L_Siguiente));
    L_DeduplicarContiguos(docs,comparar_dicts);
  /*  L_Mover_Cte(docs,L_Primero);
    if(L_Mover_Cte(docs,L_Siguiente))
    {
       L_DeduplicarContiguos(docs,comparar_dicts);
    }*/


    L_Destruir(&terminos);
    return 0;
}
