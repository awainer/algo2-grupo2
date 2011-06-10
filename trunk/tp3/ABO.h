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

/* Definiciones de punteros a función necesarios para la manipulación del ABO */

/*
 * Tipo Puntero a función de comparación para que el ABO mantenga el orden de la
 * estructura y pueda realizar las operaciónes de ABM y Obtención de datos
 */
typedef int (*taboCmp) (void*, void*);

/*
 * Función de procesamiento de todos los elementos de un ABO. El primer puntero
 * void debe usarse para pasar el elemento contenido en el ABO, y el segundo
 * está presente para admitir la utilización de argumentos, ya sean estáticos, o
 * variables, a cada invocación de procesamiento.
 */
typedef int (*aboProcessFunctionPtr) (void*, void*);

/* Fin definiciones de punteros a función */

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
