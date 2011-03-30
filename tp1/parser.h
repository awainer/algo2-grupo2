#ifndef PARSER_H_
#define PARSER_H_

#include "a_sintactico.h"
#include "a_lexico.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    E_NONE,
    E_LEXICO,
    E_SINTACTICO
}TipoError;

typedef struct t_parser{
	TSintactico * as;
	TLexico  * lex;
    TipoError ultimoError;
}TParser;

/*
 Descripción: Inicializa una nueva variable de tipo TParser.
 Precondiciones: p apunta a una variable de tipo TParser no creada previamente.
 Postcondiciones: Se inicializó la variable p.
 */
int TParser_Crear(TParser * p, TSintactico * ts, TLexico * tl);

/*
 Descripción: Coloca un nuevo carácter para ser analizado, mostrando por pantalla los mensajes
			 correspondientes.
 Precondiciones: p esta inicializado.
 Postcondiciones: Se recibió un nuevo carácter y, si corresponde, muestran por pantalla mensajes
				 correspondientes. Si ocurre un error se notifica. Si se quiere más información, se debe invocar la primitiva
				 getUltimoError.
 */
int tParser_PushChar(TParser* p, char c);

/*
 Descripción: Indica que se terminó el documento JSON actual, se reinicializa el estado interno del TDA para
			 procesar un nuevo JSON.
 Precondiciones: p esta inicializado.
 Postcondiciones: Se reinició el TDA para procesar otro flujo. Si el flujo se terminó en un  estado inconsistente
				 se devuelve un error.La forma de obtener la descripción del error es la misma que en el caso
				 de pushChar.
 */
int TParser_TerminarFlujo(TParser* p);

/*
 Descripción: Devuelve el último error ocurrido.
 Precondiciones: p esta inicializado. Ocurrió un error al procesar un flujo de caracteres.
 Postcondiciones: Se devuelve un código de error y un mensaje descriptivo del mismo.
 */
int getUltimoError(TParser * p, int codigo, char* mensaje);

/*
 Descripción:
 Precondiciones:
 Postcondiciones:
 */
int TParser_Parsear(TParser * p);

/*
 Descripción:
 Precondiciones:
 Postcondiciones:
 */
int TParser_Destruir(TParser * p);
#endif

