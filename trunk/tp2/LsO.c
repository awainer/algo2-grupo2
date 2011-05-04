#include "LsO.h"
#include <stdio.h>

void LO_Crear(TListaOrdenada *pLs, int TamanioDato,int (*cmp)(void*,void*))
{
    L_Crear(&pLs->elementos,TamanioDato);
    /*printf("%d",L_Vacia(pLs->elementos));*/
    pLs->cmp=cmp;
}


void LO_Vaciar(TListaOrdenada *pLs)
{
    L_Vaciar(&pLs->elementos);
    return;
}

int LO_Vacia(TListaOrdenada Ls)
{
    return L_Vacia(Ls.elementos);
}

void LO_Elem_Cte(TListaOrdenada Ls, void* pE)
{
    L_Elem_Cte(Ls.elementos,pE);
    return;
}

int LO_Mover_Cte(TListaOrdenada *pLs, TMovimiento_Ls M)
{
    return L_Mover_Cte(&pLs->elementos,M);
}

void LO_Borrar_Cte(TListaOrdenada *pLs)
{
    L_Borrar_Cte(&pLs->elementos);
    return;
}

int LO_Insertar(TListaOrdenada *pLs, void* E)
{ /*Aca es donde debe suceder la insercion ordenada*/
    void * aux_elem;
    int seguir=TRUE;

    /*aux_elem = malloc(sizeof(E));
    anterior = malloc(sizeof(E));*/


    /*if(LO_Vacia(*pLs))
    {
            L_Insertar_Cte(&pLs->elementos,L_Primero,E);
            free(aux_elem);
            return 0;

    }
    else
    {
      L_Mover_Cte(&pLs->elementos,L_Primero);
      L_Elem_Cte(pLs->elementos,aux_elem);
      while ( seguir &&  pLs->cmp(aux_elem,E) )
      {
      L_Elem_Cte(pLs->elementos,aux_elem);
      seguir=LO_Mover_Cte(pLs,L_Siguiente);
      }
        L_Insertar_Cte(&pLs->elementos,L_Siguiente,E);

    }
    free(aux_elem);
    return 0;
*/
L_Insertar_Cte(&pLs->elementos,L_Siguiente,E);
}

void LO_Destruir(TListaOrdenada * pLs)
{
    L_Vaciar(&pLs->elementos);
}
