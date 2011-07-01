#include "LsO.h"
#include <stdio.h>

void LO_Crear(TListaOrdenada *pLs, int TamanioDato,int (*cmp)(void*,void*))
{
    L_Crear(&pLs->elementos,TamanioDato);
    /*printf("%d",L_Vacia(pLs->elementos));*/
    pLs->tamanioDato=TamanioDato;
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
    if(LO_Vacia(*pLs)){
        return L_Insertar_Cte(&pLs->elementos,L_Primero,E);
    } else {
        aux_elem = malloc(pLs->tamanioDato);
        L_Mover_Cte(&pLs->elementos,L_Primero);
        L_Elem_Cte(pLs->elementos,aux_elem);
        while (  (pLs->cmp(aux_elem,E)<0) && (LO_Mover_Cte(pLs,L_Siguiente)) ){
            L_Elem_Cte(pLs->elementos,aux_elem);
        }

     if(pLs->cmp(aux_elem,E)>0)
     {
        free(aux_elem);
        return L_Insertar_Cte(&pLs->elementos,L_Anterior,E);
     }
     else
    {
        free(aux_elem);
        return L_Insertar_Cte(&pLs->elementos,L_Siguiente,E);
    }

    }
    /*L_Insertar_Cte(&pLs->elementos,L_Siguiente,E);
    return 0;*/


}

void LO_Destruir(TListaOrdenada * pLs)
{
    L_Destruir(&pLs->elementos);
}
