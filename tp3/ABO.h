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

/* Definiciones de punteros a funci�n necesarios para la manipulaci�n del ABO */

/*
 * Tipo Puntero a funci�n de comparaci�n para que el ABO mantenga el orden de la
 * estructura y pueda realizar las operaci�nes de ABM y Obtenci�n de datos
 */
typedef int (*taboCmp) (void*, void*);

/*
 * Funci�n de procesamiento de todos los elementos de un ABO. El primer puntero
 * void debe usarse para pasar el elemento contenido en el ABO, y el segundo
 * est� presente para admitir la utilizaci�n de argumentos, ya sean est�ticos, o
 * variables, a cada invocaci�n de procesamiento.
 */
typedef int (*aboProcessFunctionPtr) (void*, void*);

/* Fin definiciones de punteros a funci�n */

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

int ABO_ProcesarInOrden(TABO* a, aboProcessFunctionPtr process, void* args);

int ABO_ProcesarPreOrden(TABO* a, aboProcessFunctionPtr process, void* args);

int ABO_ProcesarPosOrden(TABO* a, aboProcessFunctionPtr process, void* args);

int ABO_ProcesarEnRangoInOrden(TABO* a, aboProcessFunctionPtr process, void* args, void* desde, void* hasta);

#endif /* ABO_H_ */
