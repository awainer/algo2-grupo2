/*
 * ABO.c
 *
 *  Created on: 01/06/2011
 *      Author: anibal
 */

#include "ABO.h"

int buscarElem(TABO* abo, void* elem, int* mov){
	void* currElem;
	int resMov, resCmp;
	resMov = AB_MoverCte(&(abo->a), *mov);
	if(!resMov){
		return resMov; /* Condición de corte */
	}
	currElem = malloc(abo->tamanio);
	if(!currElem){
		return RES_OUT_OF_MEMORY; /* Condición de corte por error */
	}
	AB_ElemCte(abo->a, currElem);
	resCmp = abo->fcmp(currElem, elem);
	free(currElem);
	if(resCmp < 0) { /* si curr es menor, debo seguir hacia la derecha */
		*mov = DER;
	}
	if(resCmp > 0){ /* si curr es mayor, debo seguir hacia la izquierda */
		*mov = IZQ;
	}
	if(resCmp == 0){ /* si son iguales, lo encontré */
		return TRUE; /* Condición de corte */
	} else {
		return buscarElem(abo, elem, mov); /* Llamado recursivo */
	}
}

int aboBorrarCorriente(TABO* abo);

int replaceOrDelete(TABO* ca, void* elem, int movBase, int movAlt){
	int resMov;
	TAB abAux;
	memcpy(&abAux, &(ca->a), sizeof(TAB));

	resMov = AB_MoverCte(&(ca->a), movBase);
	if(!resMov){ /* no tiene hijos menores */
		resMov = AB_MoverCte(&(ca->a), movAlt);
		if(!resMov){ /* es una hoja */
			AB_BorrarRama(&(ca->a));
			return RES_DELETED;
		} else {
			if(!AB_MoverCte(&(ca->a), movBase)){
				AB_ElemCte(ca->a, elem);
				AB_BorrarRama(&(ca->a));
				return RES_OK;
			} else {
				while(AB_MoverCte(&(ca->a), movBase));
				AB_ElemCte(ca->a, elem);
				resMov = aboBorrarCorriente(ca);
				memcpy(&(ca->a), &abAux, sizeof(TAB));
				return resMov;
			}
		}
	} else {
		if(!AB_MoverCte(&(ca->a), movAlt)){
			AB_ElemCte(ca->a, elem);
			AB_BorrarRama(&(ca->a));
			return RES_OK;
		} else {
			while(AB_MoverCte(&(ca->a), movAlt));
			AB_ElemCte(ca->a, elem);
			resMov = aboBorrarCorriente(ca);
			memcpy(&(ca->a), &abAux, sizeof(TAB));
			return resMov;
		}
	}

}

int aboBorrarCorriente(TABO* abo){
	int res = 0;
	void *substitute;
	substitute = malloc(abo->tamanio);
	if(!substitute){
		return RES_OUT_OF_MEMORY;
	}

	res = replaceOrDelete(abo, substitute, IZQ, DER);
	if(res!=RES_DELETED){
		AB_ModifCte(&(abo->a), substitute);
	}
	free(substitute);
	return RES_OK;
}

int ABO_Crear(TABO* abo, taboCmp paf, int tam){
	abo->fcmp = paf;
	abo->tamanio = tam;
	AB_Crear(&(abo->a), tam);
	return RES_OK;
}

int ABO_Destruir(TABO* abo){
	abo->fcmp = NULL;
	AB_Vaciar(&(abo->a));
	return RES_OK;
}

int ABO_Insertar(TABO* abo, void* elem){
	int resBusqueda=FALSE, mov=RAIZ;
	resBusqueda = buscarElem(abo, elem, &mov);
	if(!resBusqueda){
		return AB_Insertar(&(abo->a), mov, elem);
	}
	return RES_ELEMENTO_YA_EXISTE;
}

int ABO_Obtener(TABO* abo, void* elem){
	int resBusqueda=FALSE, mov=RAIZ;
	resBusqueda = buscarElem(abo, elem, &mov);
	if(!resBusqueda){
		return RES_ELEMENTO_NO_EXISTE;
	}
	AB_ElemCte(abo->a, elem);
	return RES_OK;
}

int ABO_Actualizar(TABO* abo, void* elem){
	int resBusqueda=FALSE, mov=RAIZ;
	resBusqueda = buscarElem(abo, elem, &mov);
	if(!resBusqueda){
		return RES_ELEMENTO_NO_EXISTE;
	}
	AB_ModifCte(&(abo->a), elem);
	return RES_OK;
}

int ABO_Borrar(TABO* abo, void* elem){
	int resBusqueda=FALSE, mov=RAIZ;
	resBusqueda = buscarElem(abo, elem, &mov);
	if(!resBusqueda){
		return RES_ELEMENTO_NO_EXISTE;
	}

	resBusqueda = aboBorrarCorriente(abo);
	if(resBusqueda==RES_DELETED){
		AB_MoverCte(&(abo->a), RAIZ);
	}
	return RES_OK;
}


