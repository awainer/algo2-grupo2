#ifndef A_LEXICO_H_INCLUDED
#define A_LEXICO_H_INCLUDED

#include "a_sintactico.h"

typedef struct tlexico{
	TSintactico * sintactico;
	int  error_codigo;
	char  error_mensaje[30];
	char  buffer[MAX_DATO];
	int   buffer_idx;

	}TLexico;

/*Descripción: Inicializa una nueva variable de tipo TLexico
Precondiciones: al apunta a una varible de tipo TLexico no creada previamente.
Postcondiciones: Se inicializó la variable al*/
int TLexico_Crear(TLexico* al);


/*Descripción: Establece el Analizador léxico que utilizará este analizador sintáctico.
Precondiciones: al esta inicializado. as esta inicializado.
Postcondiciones: Se definió el analizador sintáctico hacia donde se dirigirán los tokens*/
int TLexico_setAnalizadorSintactico(TLexico* al, TSintactico* as);


/*Descripción: Coloca un nuevo caracter para ser analizado lexicamente. Eventualmente se
generan tokens que son dirigidos hacia el analizador sintáctico.
Precondiciones: al esta inicializado. Se ha definido un analizador sintáctico.
Postcondiciones: Se recibió un nuevo carácter y si corresponde se envió un token al
analizador léxico mediante su función pushToken. Si se produce un error se devuelve,
discriminando errores generados en este TDA, o errores generados al enviar el token al
analizador sintáctico. En el primer caso se puede obtener una descripción del error mediante
la primitiva getUltimoError. En el segundo caso se debe invocar la primitiva getUltimoError
del analizador sintáctico que generó el error.*/
int TLexico_PushChar(TLexico* al, char c);

/*Descripción: Indica que se terminó el documento JSON actual, se reinicializa el estado
interno del TDA para procesar un nuevo JSON.
Precondiciones: al esta inicializado.
Postcondiciones: Se reinició el TDA para procesar otro flujo. Si el flujo terminó en un
estado inconsistente se devuelve un error. El error tambien puede generarse en el analizador
sintáctico. La forma de obtener la descripción del error es la misma que en el caso de
pushChar.*/
int TLexico_terminarFlujo(TLexico* al);

/*Descripción: Devuelve el ultimo error ocurrido.
Precondiciones: al esta inicializado. Ocurrió un error al procesar un flujo de caracteres.
Postcondiciones: Se devuelve un código de error y en mensaje un mensaje descriptivo del
mismo.*/
int TLexico_getUltimoError(TLexico* al, int * codigo, char* mensaje);


#endif
