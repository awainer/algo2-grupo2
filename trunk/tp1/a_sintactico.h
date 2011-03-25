#ifndef A_SINTACTICO_H_INCLUDED
#define A_SINTACTICO_H_INCLUDED

#include "token.h"
#include "error.h"

typedef struct tda_sintactico{
	/* El ultimo error recibido, 0 es ok. */
	int  error_codigo;
	char error_mensaje[30];
	/*El ultimo token que recibi*/
	Token	UltimoToken;
	/*en el buffer voy a ir guardando las "palabras", para mostrarlas */
	char	buffer[255];
	/* En realidad no se que tipo de dato deberia usar aca, pero quiero guardar en que 'scope' estoy, para determinar
	 que tokens son validos a cada momento */
	int		scope;
}TSintactico;



/*
Descripción: Inicializa una nueva variable de tipo TSintactico
Precondiciones: as apunta a una variable de tipo TSintactico no creada previamente.
Postcondiciones: Se inicializó la variable as*/
int TSintactico_Crear(TSintactico* as);
/*
Descripción: Coloca un nuevo token para ser analizado, mostrando por pantalla los
mensajes correspondientes.
Precondiciones: as esta inicializado.
Postcondiciones: Se muestran los mensajes en pantalla. En caso de un error sintáctico se
devuelve un valor de error, y el mismo puede ser consultado mediante la primitiva
getUltimoError
*/
int TSintactico_PushToken(TSintactico* as, Token* tk);
/*
Descripción: Indica que se terminó el documento JSON actual, se reinicializa el estado
interno del TDA para procesar un nuevo JSON.
Precondiciones: as esta inicializado.
Postcondiciones: Se reinició el TDA para procesar otro flujo. Si el flujo terminó en un
estado inconsistente se devuelve un error. La forma de obtener la descripción del error es la
misma que en el caso de pushToken.*/
int TSintactico_terminarFlujo(TSintactico* as);
/*
Descripción: Devuelve una descripción mas detallada del ultimo error ocurrido.
Precondiciones: as esta inicializado. Ocurrió un error al procesar un flujo de tokens.
Postcondiciones: Se devuelve un código de error y en mensaje un mensaje descriptivo del
mismo.*/
int TSintactico_getUltimoError(TSintactico*  as, int *codigo, char* mensaje);

#endif
