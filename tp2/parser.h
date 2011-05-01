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
	TSintactico  as;
	TLexico   lex;
    TipoError ultimoError;
    char   c;
}TParser;



int TParser_Crear(TParser* p);
/*Descripción: Inicializa una nueva variable de tipo TParser
Precondiciones: p apunta a una varible de tipo TParser no creada previamente.
Postcondiciones: Se inicializó la variable p*/
int TParser_PushChar(TParser* p, char c);
/*Descripción: Coloca un nuevo carácter para ser analizado, mostrando por pantalla los
mensajes correspondientes.
Precondiciones: p esta inicializado.
Postcondiciones: Se recibió un nuevo carácter y, si corresponde, muestran por pantalla
mensajes correspondiente. Si ocurre un error se notifica. Si se quiere mas información, se
debe invoca la primitiva getUltimoError.*/
int TParser_terminarFlujo(TParser* p);
/*Descripción: Indica que se terminó el documento JSON actual, se reinicializa el estado
interno del TDA para procesar un nuevo JSON.
Precondiciones: p esta inicializado.
Postcondiciones: Se reinició el TDA para procesar otro flujo. Si el flujo terminó en un
estado inconsistente se devuelve un error. La forma de obtener la descripción del error es la
misma que en el caso de pushChar.*/
int TParser_getUltimoError(TParser* p, int * codigo, char* mensaje);
/*Descripción: Devuelve el último error ocurrido.
Precondiciones: p esta inicializado. Ocurrió un error al procesar un flujo de caracteres.
Postcondiciones: Se devuelve un código de error y un mensaje descriptivo del mismo.
*/

/*
Descripción: Forma de comunicarse con el exterior. Se establece ante la ocurrencie del evento "evento". De haber sido definida previamente se reemplaza
por esta nueva.
Precondiciones: ts ha sido creado.
Postcondiciones: se establece la callback a llamar ante la ocurrencia del evento "evento". Si ya se había definido la callback se reemplaza por esta
nueva.
*/
/*int TParser_setCallback (TSintactico *ts, int evento, void* tda_contexto, int(*callback)(const void*, int, const void*));*/
int TParser_setCallback (TParser *p, int evento, void* tda_contexto, int(*callback)( void*,  void*));


#endif

