#include "AB.h"

void AB_Crear(TAB *a,int tdato)
{
	a->tamdato = tdato;
	a->raiz = NULL;
	a->cte = NULL;
}

void AB_ElemCte(TAB a,void *elem)
{
	memcpy(elem,a.cte->elem,a.tamdato);
}

void AB_ModifCte(TAB *a,void *elem)
{
	memcpy(a->cte->elem,elem,a->tamdato);
}

TNodoAB* BuscarPadre(TNodoAB *padre,TNodoAB *hijo)
{
	TNodoAB *paux = NULL;
	if ((padre->izq == hijo) || (padre->der == hijo))
		return padre;
	else
	{
		if (padre->izq != NULL)
			paux = BuscarPadre(padre->izq,hijo);
		if ((padre->der != NULL) && (paux == NULL))
			paux = BuscarPadre(padre->der,hijo);
		return paux;
	}
}

int AB_MoverCte(TAB *a,int mov)
{
	int movio = TRUE;
	switch (mov)
	{
		case IZQ : if (a->cte->izq != NULL)
						a->cte = a->cte->izq;
					else
						movio = FALSE;
					break;
		case DER : if (a->cte->der != NULL)
						a->cte = a->cte->der;
					else
						movio = FALSE;
					break;
		case PAD : if (a->cte != a->raiz)
						a->cte = BuscarPadre(a->raiz,a->cte);
					else
						movio = FALSE;
					break;
		case RAIZ : if (a->raiz != NULL)
						a->cte = a->raiz;
					else
						movio = FALSE;
					break;
		default : movio = FALSE;
	}
	return movio;
}

void VaciarSub(TNodoAB *pnodo)
{
	if (pnodo != NULL)
	{
		if (!((pnodo->izq == NULL) && (pnodo->der == NULL)))
		{
			VaciarSub(pnodo->izq);
			VaciarSub(pnodo->der);
		}
		free(pnodo->elem);
		free(pnodo);
	}
}

void AB_Vaciar(TAB *a)
{
	VaciarSub(a->raiz);
	a->raiz = NULL;
	a->cte = NULL;
}

int AB_Insertar(TAB *a,int mov,void *elem)
{
	TNodoAB *paux;
	int inserto = TRUE;
	paux = (TNodoAB*) malloc(sizeof(TNodoAB));
	paux->izq = NULL;
	paux->der = NULL;
	if (paux)
	{
		paux->elem = malloc(a->tamdato);
		if (paux->elem)
		{
			memcpy(paux->elem,elem,a->tamdato);
			switch(mov)
			{
				case IZQ : if (a->cte->izq == NULL)
								a->cte->izq = paux;
							 else
								inserto = FALSE;
							 break;
				case DER : if (a->cte->der == NULL)
								a->cte->der = paux;
							 else
								inserto = FALSE;
							 break;
				case RAIZ : if (a->raiz == NULL)
								a->raiz = paux;
							else
								inserto = FALSE;
							break;
				default : inserto = FALSE;
			}
			if (!inserto)
			{
				free(paux->elem);
				free(paux);
				return inserto;
			}
			else{
				a->cte = paux;
				return TRUE;
			}
		}
		else /* if (paux->elem) ->*/
		{
			free(paux);
			return FALSE;
		}
	}
	else /* if (paux) */
	{
		free(paux);
		return FALSE;
	}
}
	
int AB_Vacio(TAB a)
{	
	return (a.raiz == NULL);
}


int AB_BorrarRama(TAB *a){
	if(a->raiz!=NULL){
		TNodoAB* padre;
		if(a->raiz!=a->cte){
			padre = BuscarPadre(a->raiz, a->cte);
			if(padre->izq==a->cte){
				padre->izq = NULL;
			} else {
				padre->der = NULL;
			}
		} else {
			padre = a->raiz = NULL;
		}
		VaciarSub(a->cte);
		a->cte = padre;
		return RES_OK;
	}
	return RES_ARBOL_VACIO;
}

int AB_BorrarSubRama(TAB *a, int mov){
	if(mov==IZQ){
		VaciarSub(a->cte->izq);
		a->cte->izq = NULL;
	} else if(mov==DER) {
		VaciarSub(a->cte->der);
		a->cte->der = NULL;
	} else {
		return RES_MOV_INVALIDO;
	}
	return RES_OK;
}
