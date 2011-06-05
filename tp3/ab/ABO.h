/*
 * ABO.h
 *
 *  Created on: 01/06/2011
 *      Author: anibal
 */

#ifndef ABO_H_
#define ABO_H_

#include "AB.h"
#include <stdlib.h>

#define RES_DELETED 1
#define RES_OK 0
#define RES_ELEMENTO_YA_EXISTE -1
#define RES_OUT_OF_MEMORY -2
#define RES_ELEMENTO_NO_EXISTE -3


typedef int (*taboCmp) (void*, void*);

typedef struct T_ABO {
	int tamanio;
	taboCmp fcmp;
	TAB a;
}TABO;

int ABO_Crear(TABO* abo, taboCmp paf, int tam);

int ABO_Destruir(TABO* abo);

int ABO_Insertar(TABO* abo, void* elem);

int ABO_Obtener(TABO* abo, void* elem);

int ABO_Actualizar(TABO* abo, void* elem);

int ABO_Borrar(TABO* abo, void* elem);

#endif /* ABO_H_ */
