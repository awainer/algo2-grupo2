#include "dict.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OOM_ERROR -1
#define ERR_VACIO 2
#define RES_OK 0

int TDiccionaro_Crear(TDiccionario* td)
{
    L_Crear(&td->elementos,sizeof(Definicion));

    return 0;
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

/*pre: El diccionario ha sido creado
post: Se coloca en el diccionario el equivalente a diccionario[clave] = valor. Si clave ya existia en el
diccionario, su valor se reemplaza por el nuevo. Se coloca una copia del texto (no un puntero).*/
int TDiccionario_colocar(TDiccionario* td, char* clave, char* valor)
{
    Definicion def;

    def.k=(char *)malloc(strlen(clave));
    if (def.k==NULL)
    {
        return OOM_ERROR;
    }

    def.v=(char *)malloc(strlen(valor));

    if (def.v==NULL)
    {
        free(def.k);
        return OOM_ERROR;
    }


    strcpy(def.k,clave);
    strcpy(def.v,valor);


    /* Caso en que agrego*/
    L_Insertar_Cte(&td->elementos, L_Siguiente, (void *)&def);

    /* TODO modificar clave*/
    return 0;
}

/*pre: El diccionario ha sido creado. Existe la entrada “clave” en el diccionario. Buffer tiene el
tamaño suficiente para guardar el texto
post: se guarda en buffer una copia del texto en el diccionario bajo la clave. Es el equivalente a
buffer = diccionario[clave]*/
int TDiccionario_obtener(TDiccionario* td, char* clave, char* buffer)
{
    return 0;
}
/*pre: el diccionario ha sido creado
post: devuelve el tamaño del texto asociado con la clave a fin de poder reservar un buffer donde
quepa el texto y obtenerlo con Tdiccionario_obtener. Si la clave no esta en el diccionario devuelve
0.*/
int  TDiccionario_sizeDato(TDiccionario* td, char* clave)
{
    Definicion * aux=NULL; /* Aca uso un void* porque es lo que devuelve L_Elem_Cte */
    int largo,seguir;
    /*TODO free*/
    aux=(Definicion *)malloc(sizeof(Definicion));

    if(L_Vacia(td->elementos))
    {
          free(aux);
          return 0;
    }
    else
    {
        L_Mover_Cte(&td->elementos,L_Primero);
        L_Elem_Cte(td->elementos,(void *)aux);
        if (!strcmp(aux->k,clave))
            {
                /* primer elemento coincide*/
                largo = strlen(aux->v);
                free(aux);
                return largo;
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
            largo = strlen(aux->v);
            free(aux);
            return largo;
        }
        /*( (L_Mover_Cte(&td->elementos,L_Siguiente)) && strcmp( (Definicion*)aux->k,clave ) )*/
    }
   free(aux);
   return 0;
}
