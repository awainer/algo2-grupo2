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
int diccionario_existeValor(TDiccionario* td,char * clave,Definicion * aux)
{
    int seguir;


        if(L_Vacia(td->elementos))
    {
          aux=NULL;
          return ERR_NA;
    }
    else
    {
        L_Mover_Cte(&td->elementos,L_Primero);
        L_Elem_Cte(td->elementos,(void *)aux);
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




    if(diccionario_existeValor(td,clave,&aux)==0)
    {
    /*Si mi diccionario ya tiene una entrada para esta clave, la borro antes de insertar la nueva*/
    /*Creo que seria un poco mas rapido solo hacer free del valor y copiarlo, pero seria mucho mas desprolijo */
        L_Elem_Cte(td->elementos,&aux);
        free(aux.k);
        free(aux.v);
        L_Borrar_Cte(&td->elementos);
    }

    strcpy(def.k,clave);
    strcpy(def.v,valor);
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
    return 0;
}


/*pre: El diccionario ha sido creado. Existe la entrada “clave” en el diccionario. Buffer tiene el
tamaño suficiente para guardar el texto
post: se guarda en buffer una copia del texto en el diccionario bajo la clave. Es el equivalente a
buffer = diccionario[clave]*/
int TDiccionario_obtener(TDiccionario* td, char* clave, char* buffer)
{
    Definicion aux;
    diccionario_existeValor(td,clave,&aux); /*En este caso, no me importa el valor de retorno porque la precondicion dice que existe la entrada */
    strcpy(buffer,aux.v);

    return 0;
}


/*pre: el diccionario ha sido creado
post: devuelve el tamaño del texto asociado con la clave a fin de poder reservar un buffer donde
quepa el texto y obtenerlo con Tdiccionario_obtener. Si la clave no esta en el diccionario devuelve
0.*/
int  TDiccionario_sizeDato(TDiccionario* td, char* clave)
{
    Definicion aux;
    if(diccionario_existeValor(td,clave,&aux)==0)
    {
        return strlen(aux.v)+1;
    }
    else
        return 0;
}
