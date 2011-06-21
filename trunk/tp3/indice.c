#include "indice.h"
#include <stdio.h>

int comparar_tweet_id(void * v1, void * v2)
{
    tweet_id  *t1,*t2;
    int aux;

    t1=v1;
    t2=v2;
    aux=strcmp(t1->user,t2->user);

    if(aux!=0) return aux;
    else{
        return strcmp(t1->date,t2->date);
        }

    return 0;
}
int comparar_termino(void * v1, void * v2)
{
    TNodo_Termino * n1, *n2;
    n1=v1;
    n2=v2;
    /*printf("comparo terminos %s %s %d \n",n1->clave,n2->clave,strlen(n1->clave));*/
    return strcmp(n1->clave,n2->clave);
    /*return 0;*/
}
/*optimizo_arbol_terminos tiene como funcion insertar los datos que se le estan agregando. */
int optimizo_arbol_terminos (void* v1, void * v2)
{
    TListaSimple lista_terminos;
    TNodo_Termino aux_nodo_termino;
    TNodo_Tweet *aux_nodo_tweet;
    TIndice *ti;

    aux_nodo_tweet = v1;
    ti = v2;

    L_Crear(&lista_terminos, STRING_LEN);
    Ttokenizer_analizar(ti->tk,aux_nodo_tweet->clave.user,&lista_terminos);
    L_Mover_Cte(&lista_terminos,L_Primero);

    do
    {
        L_Elem_Cte(lista_terminos,&aux_nodo_termino.clave);
        if(!ABO_Obtener(&ti->terminos,aux_nodo_termino.clave))
        {
          /*  printf("termino repetido %s\n",aux_nodo_termino.clave);*/
            L_Insertar_Cte(&aux_nodo_termino.dato,L_Siguiente,&aux_nodo_tweet->clave);
            ABO_Actualizar(&ti->terminos,&aux_nodo_termino);
        }
        else
        {
            /*Preparo el dato que voy a insertar*/
            L_Crear(&aux_nodo_termino.dato,sizeof(tweet_id));
            L_Insertar_Cte(&aux_nodo_termino.dato,L_Siguiente,&aux_nodo_tweet->clave); /*este es el tweet_id del tw que venimos procesando*/
            ABO_Insertar(&ti->terminos,&aux_nodo_termino);
        }

    }while (L_Mover_Cte(&lista_terminos,L_Siguiente));



    L_Destruir(&lista_terminos);

    return 0;
}

int borrar_arbol_terminos(void *v1, void*v2)
{
    TABO *arbolTerminos;
    TNodo_Termino * n1;

    arbolTerminos = v2;
    n1 = v1;

    ABO_Borrar(arbolTerminos, n1);

    return 0;
}
int borrar_arbol_tweets (void *v1, void *v2)
{
    TABO *arbolTweets;
    TNodo_Tweet *n1;

    arbolTweets = v2;
    n1 = v1;
    Tdiccionario_Destruir(&n1->valor);
    ABO_Borrar(arbolTweets, n1);
    return 0;
}

int borrar_tweet_por_fecha(void * t,void * v2)
{
    TNodo_Tweet * nodo=t;
    printf("X %s %s \n",nodo->clave.user, nodo->clave.date);
    return 0;
}

int comparar_usuario_y_borrarlo(void *v1, void *v2){
    TABO *arbolTweets;
    TNodo_Tweet *n1;
    void ** aux=v2;
    char * usuario=(char*)aux[0];

    printf("recibo %s\n",(char*)aux[0]);

    if ((strcmp(n1->clave.user, usuario) == NULL)){
        Tdiccionario_Destruir(&n1->valor);
        ABO_Borrar(&arbolTweets->a, n1);
        return TRUE;
    }
    else  return FALSE;
}




int TIndice_crear(TIndice* ti, TTokenizer* ta)
{
    ABO_Crear(&ti->terminos,comparar_termino,sizeof(TNodo_Termino));
    ABO_Crear(&ti->tweets,comparar_tweet_id,sizeof(TNodo_Tweet));
    ti->tk=ta;
    return 0;
}
/*pre: el índice fue creado
post: los recursos del índice fueron liberados*/
int TIndice_destruir(TIndice* ti)
 {
        /*Recorro el arbol de tweets borrando todo.*/
        ABO_ProcesarPosOrden(&ti->tweets, borrar_arbol_tweets, &ti->tweets);
        /*Recorro el arbol de terminos borrando todo.*/
        ABO_ProcesarPosOrden(&ti->terminos,borrar_arbol_terminos, &ti->terminos);
        /*Arbol de tweets y arbol de terminos borrados. */
        /*Una vez vaciados los arboles, los destruyo. */
        ABO_Destruir(&ti->tweets);
        ABO_Destruir(&ti->terminos);
        return 0;
}


void obtener_id(TDiccionario* tw,tweet_id * id)
{
    int s;
    s=TDiccionario_sizeDato(tw,"user_screen_name");
    TDiccionario_obtener(tw,"user_screen_name",id->user);
    s=TDiccionario_sizeDato(tw,"created_at");
    TDiccionario_obtener(tw,"created_at",id->date);
}

/*pre: el índice fue creado
post: se agregó un nuevo Tweet al índice El texto indexado es el
que esta en el campo “text” del Tweet*/
int TIndice_agregar(TIndice* ti, TDiccionario* Tweet)
{
    TNodo_Tweet   aux_nodo_tweet;
    TNodo_Termino aux_nodo_termino;
    TListaSimple  lista_terminos;
    int s=0;
    char *   texto;
/*    char buffer_termino[255];*/

    /*cargo el nodo tweet y lo inserto*/
    obtener_id(Tweet,&aux_nodo_tweet.clave);
    /*aux_nodo_tweet.valor=*Tweet;*/
    memcpy(&aux_nodo_tweet.valor,Tweet,sizeof(TDiccionario));



    if (ABO_Obtener(&ti->tweets,&aux_nodo_tweet) == RES_OK)
        {
            printf("Error: Tweet repetido: %s, %s\n",aux_nodo_tweet.clave.user, aux_nodo_tweet.clave.date);
            return 1;
        }
    else
        {
            printf("inserto %s, %s\n",aux_nodo_tweet.clave.user, aux_nodo_tweet.clave.date);
            ABO_Insertar(&ti->tweets,&aux_nodo_tweet);
        }
    /*ahora empiezo con los terminos*/

    s=TDiccionario_sizeDato(Tweet,"text");
    texto=malloc(s);
    TDiccionario_obtener(Tweet,"text",texto);

    L_Crear(&lista_terminos,STRING_LEN);
    Ttokenizer_analizar(ti->tk,texto,&lista_terminos);


    L_Mover_Cte(&lista_terminos,L_Primero);
    do /*itero por la lista de terminos tokenizada*/
    {
        L_Elem_Cte(lista_terminos,&aux_nodo_termino.clave);
        /*printf("%s\n",aux_nodo_termino.clave);*/
        if(ABO_Obtener(&ti->terminos,&aux_nodo_termino)==RES_OK)
        {
            L_Insertar_Cte(&aux_nodo_termino.dato,L_Siguiente,&aux_nodo_tweet.clave);
            ABO_Actualizar(&ti->terminos,&aux_nodo_termino);
            /*debug*/
            /*{
            tweet_id tid;
            printf("termino repetido %s\n",aux_nodo_termino.clave);
            ABO_Obtener(&ti->terminos,&aux_nodo_termino);
            L_Mover_Cte(&aux_nodo_termino.dato,L_Primero);
            do
            {
                L_Elem_Cte(aux_nodo_termino.dato,&tid);
                printf("%s, %s\n",tid.date, tid.user );
            } while(L_Mover_Cte(&aux_nodo_termino.dato,L_Siguiente));
            }*//*fin debug*/

        }
        else
        {
            /*printf("nuevo termino %s\n",aux_nodo_termino.clave);*/
            /*Preparo el dato que voy a insertar*/
            L_Crear(&aux_nodo_termino.dato,sizeof(tweet_id));
            L_Insertar_Cte(&aux_nodo_termino.dato,L_Primero,&aux_nodo_tweet.clave); /*este es el tweet_id del tw que venimos procesando*/
            ABO_Insertar(&ti->terminos,&aux_nodo_termino);

        }

    }while (L_Mover_Cte(&lista_terminos,L_Siguiente));



    L_Destruir(&lista_terminos);

    free(texto);
    return 0;
}


int imprimirIDs(void * v1, void * v2)
{
    tweet_id * aux;
    printf("%s %s\n",aux->date,aux->user);
    return 0;
}
/*pre: el índice fue creado. Docs es una lista de TDiccionario* que
se cargará con Tweets.
post: carga en la lista “docs” pasada como parámetro, los punteros
a TDiccionario que contienen el término. Si el termino no se
encuentra en el índice, la lista se deja vacía.*/
int TIndice_listarDocs(TIndice* ti, char* termino, TListaSimple * docs)
{

    TNodo_Termino aux_ntermino;
    TNodo_Tweet   aux_ntweet;



    strcpy(aux_ntermino.clave,termino);

    /*if(!L_Vacia(aux_ntermino.dato))*/
    if(ABO_Obtener(&ti->terminos,&aux_ntermino) == RES_OK)
    {
        L_Mover_Cte(&aux_ntermino.dato,L_Primero);
        do{
            /*L_Elem_Cte(aux_ntermino.dato,&aux_ntweet);*/
            L_Elem_Cte(aux_ntermino.dato,&aux_ntweet.clave);
            ABO_Obtener(&ti->tweets,&aux_ntweet);
            L_Insertar_Cte(docs,L_Siguiente,&aux_ntweet.valor);
           }while (L_Mover_Cte(&aux_ntermino.dato,L_Siguiente));

    }

    return 0;
}
/*pre: el índice fue creado
post: elimina el Tweet identificado por el usuario y fecha pasados
como parámetros.*/
int TIndice_eliminarTweet(TIndice* ti, char* usuario, char* fecha)
{

    TNodo_Tweet aux2;

    strcpy(aux2.clave.date,fecha);
    strcpy(aux2.clave.user,usuario);
    if(ABO_Obtener(&ti->tweets,&aux2))
    {
        Tdiccionario_Destruir(&aux2.valor);
        ABO_Borrar(&ti->tweets,&aux2);
    }


    return 0;
}
/*pre: el índice fue creado
post: elimina todos los Tweets del usuario pasado como parámetro.*/
int TIndice_eliminarUsuario(TIndice* ti, char* usuario)
{
    /* Argumento es un array de dos punteros a cualquier cosa; en la primera posicion hay un puntero a char* usuario y en la segunda a arbol de tweets. */
    void * argumento[2];

    argumento[0]=usuario;
    argumento[1]=&ti->tweets;
    ABO_ProcesarPosOrden(&ti->tweets, comparar_usuario_y_borrarlo, argumento);

    return 0;
}
/*pre: el índice fue creado
post: Reconstruye el índice haciendo más eficiente la búsqueda.
Los Tweets que contiene después de optimizar deben ser los mismos
que antes de optimizar. Ver notas de implementación.*/
int TIndice_optimizar(TIndice* ti)
{
    /*TNodo_Tweet tweetAux;
    TNodo_Termino terminoAux;*/

    /*Descarto el arbol de terminos. */
    ABO_ProcesarPosOrden(&ti->terminos, borrar_arbol_terminos, &ti->terminos);
    /*Hago recorrido completo del arbol de tweets, analizando por cada uno nuevamente con el tokenizer y volviendo a cargar los terminos de cada uno en el arbol de terminos */
    ABO_ProcesarPosOrden(&ti->tweets, optimizo_arbol_terminos, ti);

    return 0;
}
