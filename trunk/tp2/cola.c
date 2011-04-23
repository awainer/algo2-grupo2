#include "Cola.h"

/*C_CREAR
Pre: C no fue creada.
Post: C creada y vac�a. */
void C_Crear(TCola *pC, int TamanioDato)
{
	pC->Primero = pC->Ultimo = NULL;
	pC->TamanioDato = TamanioDato;
}

/*C_VACIAR
Pre: C creada.
Post: C vac�a. */
void C_Vaciar(TCola *pC)
{
	TNodoCola *pAux = pC->Primero;
	TNodoCola *pSig;
	while (pAux)
	{
		pSig = pAux->Sig;
		free(pAux->Elem);
		free(pAux);
		pAux = pSig;
	}
	pC->Primero = pC->Ultimo = NULL;
}

/*C_VACIA
Pre: C creada.
Post: Si C est� vac�a devuelve TRUE, sino FALSE. */
int C_Vacia(TCola C)
{
	return (C.Primero==NULL);
}

/*C_AGREGAR
Pre: C creada.
Post: E se agreg� como �ltimo elemento de C.
Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
int C_Agregar(TCola *pC, void* pE)
{
	TNodoCola *pNodo = (TNodoCola*) malloc(sizeof(TNodoCola));
	if (!pNodo)
		return FALSE;
	else
	{
		if (pC->Ultimo)
			pC->Ultimo->Sig = pNodo;
		if (!pC->Primero) /*Est� vac�a*/
			pC->Primero = pNodo;
		pNodo->Sig = NULL;
		pC->Ultimo = pNodo;
		pNodo->Elem = malloc (pC->TamanioDato);
		if(!pNodo->Elem)
		{
			free(pNodo);
			return FALSE;
		}
		memcpy(pNodo->Elem, pE, pC->TamanioDato);
		return TRUE;
	}
}

/*C_SACAR
Pre: C creada y no vac�a.
Post: Se extrajo de C el primer elemento y se devuelve en E.
Si no pudo extraer el elemento (porque C estaba vac�a) devuelve FALSE,
sino devuelve TRUE.*/
int C_Sacar(TCola *pC, void* pE)
{
	TNodoCola *pAux = pC->Primero;
	if (!pC->Primero)
		return FALSE;
	pC->Primero = pC->Primero->Sig;
	if (!pC->Primero)
	{
		pC->Ultimo = NULL;
	}
	memcpy(pE, pAux->Elem, pC->TamanioDato);
	free(pAux->Elem);
	free(pAux);
	return TRUE;
}

