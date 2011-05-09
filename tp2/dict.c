#include "dict.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OOM_ERROR -1
#define ERR_VACIO 2
#define RES_OK 0
#define ERR_NA -2

int TDiccionaro_Crear(TDiccionario* td)
{
    L_Crear(&td->elementos,sizeof(Definicion));
    return 0;

}






/*
pre: diccionario creado
post: devuelve RES_OK si el diccionario tiene una entrada para la clave dada, devuevle en aux un puntero a esa entrada
en caso contrario devuelve ERR_NA y NULL en aux
*/
int diccionario_getValor(TDiccionario* td,char * clave,Definicion * aux)
{
    int seguir;

        /*chequeo de Diccionario/lista vacia*/
        if(L_Vacia(td->elementos))
    {
          aux=NULL;
          return ERR_NA;
    }
    else
    {
        L_Mover_Cte(&td->elementos,L_Primero);
        /*L_Elem_Cte(td->elementos,(void *)aux);*/
        L_Elem_Cte(td->elementos,aux);
        if (!strcmp(aux->k,clave))
            {
                /* primer elemento coincide*/
                return RES_OK;
            }
        else
         {
           seguir=L_Mover_Cte(&td->elementos,L_Siguiente);
           while( strcmp(aux->k,clave)  && seguir )
                {
                L_Elem_Cte(td->elementos,aux);
                seguir=L_Mover_Cte(&td->elementos,L_Siguiente);
                }
         }

    if (!strcmp(aux->k,clave))
        {

            return RES_OK;
        }
    }
        aux=NULL;
        return ERR_NA;
}

int diccionario_getSize(TDiccionario* td,char * clave)
{
    int seguir;
    Definicion aux;
        /*chequeo de Diccionario/lista vacia*/
        if(L_Vacia(td->elementos))
    {

          return 0;
    }
    else
    {
        L_Mover_Cte(&td->elementos,L_Primero);
        /*L_Elem_Cte(td->elementos,(void *)aux);*/
        L_Elem_Cte(td->elementos,&aux);
        if (!strcmp(aux.k,clave))
            {
                /* primer elemento coincide*/
                return strlen(aux.v);
            }
        else
         {
           seguir=L_Mover_Cte(&td->elementos,L_Siguiente);
           while( strcmp(aux.k,clave)  && seguir )
                {
                L_Elem_Cte(td->elementos,&aux);
                seguir=L_Mover_Cte(&td->elementos,L_Siguiente);
                }
         }
        return(strlen(aux.v));
    /*if (!strcmp(aux.k,clave))
        {

            return RES_OK;
        }*/
    }

}


/*pre: El diccionario ha sido creado
post: Se coloca en el diccionario el equivalente a diccionario[clave] = valor. Si clave ya existia en el
diccionario, su valor se reemplaza por el nuevo. Se coloca una copia del texto (no un puntero).*/
int TDiccionario_colocar(TDiccionario* td, char* clave, char* valor)
{
    Definicion def,aux;

    def.k=(char *)malloc(strlen(clave)+1);
    if (def.k==NULL)
    {
        return OOM_ERROR;
    }

    def.v=(char *)malloc(strlen(valor)+1);

    if (def.v==NULL)
    {
        free(def.k);
        /*free(def.v);*/
        return OOM_ERROR;
    }




    if(diccionario_getValor(td,clave,&aux)==0)
    {
    /*Si mi diccionario ya tiene una entrada para esta clave, la borro antes de insertar la nueva*/
    /*Creo que seria un poco mas rapido solo hacer free del valor y copiarlo, pero seria mucho mas desprolijo */
        L_Elem_Cte(td->elementos,&aux);
        free(aux.k);
        free(aux.v);
        L_Borrar_Cte(&td->elementos);
    }

    strcpy(def.k,clave);
    strcpy(def.v,valor); /***TODO revisar este return***/
    return L_Insertar_Cte(&td->elementos, L_Siguiente, (void *)&def);


}


/*pre: El diccionario ha sido creado
post: Se liberaron los recursos asociados al diccionario*/

int Tdiccionario_Destruir(TDiccionario* td)
{
        Definicion auxdef;

        while(!L_Vacia(td->elementos))
        {
        L_Mover_Cte(&td->elementos,L_Primero);
        L_Elem_Cte(td->elementos,&auxdef);
        free(auxdef.k);
        free(auxdef.v);
        L_Borrar_Cte(&td->elementos);
       }
        L_Destruir(&td->elementos);
    return 0;
}


/*pre: El diccionario ha sido creado. Existe la entrada “clave” en el diccionario. Buffer tiene el
tamaño suficiente para guardar el texto
post: se guarda en buffer una copia del texto en el diccionario bajo la clave. Es el equivalente a
buffer = diccionario[clave]*/
int TDiccionario_obtener(TDiccionario* td, char* clave, char* buffer)
{
    Definicion aux;
    diccionario_getValor(td,clave,&aux); /*En este caso, no me importa el valor de retorno porque la precondicion dice que existe la entrada */
    strcpy(buffer,aux.v);

    return 0;
}


/*pre: el diccionario ha sido creado
post: devuelve el tamaño del texto asociado con la clave a fin de poder reservar un buffer donde
quepa el texto y obtenerlo con Tdiccionario_obtener. Si la clave no esta en el diccionario devuelve
0.*/
int  TDiccionario_sizeDato(TDiccionario* td, char* clave)
{
    /*if(diccionario_getValor(td,clave,&aux)==0)
    {
        return strlen(aux.v)+1;
    }
    else
        return 0;*/
    return diccionario_getSize(td,clave)+1;
}

int compstr(const void *s1, const void *s2)
{
    char * aux1, * aux2;
    int i=0;
    /*Hago esto para no tener que estar todo el tiempo casteando,
    esta funcion tiene que recibir const void* para poder usarla en qsort*/
    aux1=(char*)s1;
    aux2=(char*)s2;
    if (!strcmp(aux1,aux2))
    {
        return 1;
    }
    while ((aux1[i]==aux2[i]) && (aux1[i]!=0 ) && (aux1[i]!=0 ) )
        i++;
    if (aux1[i] > aux2[i])
        return 0;
    else
        return -1;
}

