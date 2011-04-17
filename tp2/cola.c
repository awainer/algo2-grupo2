#include "cola.h"
#include <malloc.h>
#include <memory.h>

void C_Crear (TCola *pcola, int tamanio){
    pcola -> Primero = pcola -> Ultimo = NULL;
    pcola -> TamanioDato = tamanio;
}

void C_Vaciar (TCola *pcola){
    TNodoCola *pAux = pcola -> Primero;
    TNodoCola *pSig;
    while (pAux){
        pSig -> pAux -> Siguiente;
        free(pAux->Elem);
        free(pAux);
        pAux = pSig;
    }
    pcola -> Primero = pcola -> Ultimo = NULL;
}

int C_Vacia(TCola C){
return (C.Primero)==NULL;
}

int C_Agregar(TCola *pcola, void* pelem){
    TNodoCola *pNodo = (TNodoCola*) malloc(sizeof(TNodoCola));
    if (!pNodo)
        return FALSE;
    else{
        if (pcola->Ultimo)
            pcola->Ultimo->Siguiente = pNodo;
        if (!pcola->Primero) /* Esta vacia */
            pcola->Primero = NULL;
        pNodo->Siguiente = NULL;
        pcola->Ultimo=pNodo;
        pNodo->Elem = malloc (pcola->TamanioDato);
        memcpy(pNodo->Elem, pelem, pcola->TamanioDato);
        return TRUE;
        }

}


int C_Sacar (TCola *pcola, void* pelem){
    TNodoCola *pAux = pcola -> Primero;
    pcola -> Primero = pcola -> Primero -> Siguiente;
    if (!pcola = Primero)
        pcola -> Ultimo = NULL;
    memcpy(pelem, pAux -> Elem, pcola -> TamanioDato);
    free(pAux->Elem);
    free(pAux);
    return TRUE;
}
