#include "dict.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int TDiccionaro_Crear(TDiccionario* td)
{
    L_Crear(&td->elementos,2*sizeof(int*));
    td->cantidad=0;
    return 0;
}

/*pre: El diccionario ha sido creado
post: Se liberaron los recursos asociados al diccionario*/
int Tdiccionario_Destruir(TDiccionario* td)
{   int i;
    Definicion * auxdef=NULL;

    L_Mover_Cte(&td->elementos,L_Primero);

    for(i=0;i!=td->cantidad;i++)
    {
        L_Elem_Cte(td->elementos,auxdef);
        /*printf("%s",auxdef->k);*/
        free(auxdef->k);
        free(auxdef->v);
        L_Borrar_Cte(&td->elementos);
    }

    return 0;
}

/*pre: El diccionario ha sido creado
post: Se coloca en el diccionario el equivalente a diccionario[clave] = valor. Si clave ya existia en el
diccionario, su valor se reemplaza por el nuevo. Se coloca una copia del texto (no un puntero).*/
int TDiccionario_colocar(TDiccionario* td, char* clave, char* valor)
{
    Definicion auxdef;

    /*
    FIXME: tengo que chequear primero si no existe un par con esa clave y modificar el valor!!!
    */

    auxdef.k=(char *)malloc(strlen(clave));
    auxdef.v=(char *)malloc(strlen(valor));
    if( (auxdef.v==NULL) || (auxdef.k==NULL) )
    {
        /*fallo un malloc!*/
        return -1;
    }
    strcpy(auxdef.k,clave);
    strcpy(auxdef.v,valor);
    L_Insertar_Cte(&td->elementos,L_Siguiente,&auxdef);
    return 0;
}

/*pre: El diccionario ha sido creado. Existe la entrada “clave” en el diccionario. Buffer tiene el
tamaño suficiente para guardar el texto
post: se guarda en buffer una copia del texto en el diccionario bajo la clave. Es el equivalente a
buffer = diccionario[clave]*/
int TDiccionario_obtener(TDiccionario* td, char* clave, char* buffer)
{
/*    strcpy()*/
    return 0;
}
/*pre: el diccionario ha sido creado
post: devuelve el tamaño del texto asociado con la clave a fin de poder reservar un buffer donde
quepa el texto y obtenerlo con Tdiccionario_obtener. Si la clave no esta en el diccionario devuelve
0.*/
int TDiccionario_sizeDato(TDiccionario* td, char* clave)
{
    Definicion * auxdef=NULL;

    int i,d=0;

    L_Mover_Cte(&td->elementos,L_Primero);
    L_Elem_Cte(td->elementos,auxdef);
    /*busqueda secuencial ineficiente, reemplazar por algo mejor*/
for(i=0;i!=td->cantidad;i++)
    {
      if(strncmp(clave,auxdef->k,d)) /*FIXME no se para que quiero d*/
        {
            return strlen(auxdef->v);
        }
      else
      {
        L_Mover_Cte(&td->elementos,L_Siguiente);
        L_Elem_Cte(td->elementos,auxdef);
      }

    }
    return 0;
}
