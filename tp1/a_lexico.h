#define A_LEXICO_H_INCLUDED
#define A_LEXICO_H_INCLUDED

#include "a_sintactico.h"
#include "error.h"

typedef struct tlexico{
	TSintactico * sintactico;
	TError error;
	char set_caracteres[2][200];
	}TLexico;

/*Descripci�n: Inicializa una nueva variable de tipo TLexico
Precondiciones: al apunta a una varible de tipo TLexico no creada previamente.
Postcondiciones: Se inicializ� la variable al*/
int TLexico_Crear(TLexico* al);


/*Descripci�n: Establece el Analizador l�xico que utilizar� este analizador sint�ctico.
Precondiciones: al esta inicializado. as esta inicializado.
Postcondiciones: Se defini� el analizador sint�ctico hacia donde se dirigir�n los tokens*/
int TLexico_setAnalizadorSintactico(TLexico* al, TSintactico* as);


/*Descripci�n: Coloca un nuevo caracter para ser analizado lexicamente. Eventualmente se
generan tokens que son dirigidos hacia el analizador sint�ctico.
Precondiciones: al esta inicializado. Se ha definido un analizador sint�ctico.
Postcondiciones: Se recibi� un nuevo car�cter y si corresponde se envi� un token al
analizador l�xico mediante su funci�n pushToken. Si se produce un error se devuelve,
discriminando errores generados en este TDA, o errores generados al enviar el token al
analizador sint�ctico. En el primer caso se puede obtener una descripci�n del error mediante
la primitiva getUltimoError. En el segundo caso se debe invocar la primitiva getUltimoError
del analizador sint�ctico que gener� el error.*/
int TLexico_PushChar(TLexico* al, char c);

/*Descripci�n: Indica que se termin� el documento JSON actual, se reinicializa el estado
interno del TDA para procesar un nuevo JSON.
Precondiciones: al esta inicializado.
Postcondiciones: Se reinici� el TDA para procesar otro flujo. Si el flujo termin� en un
estado inconsistente se devuelve un error. El error tambien puede generarse en el analizador
sint�ctico. La forma de obtener la descripci�n del error es la misma que en el caso de
pushChar.*/
int TLexico_terminarFlujo(TLexico* al);

/*Descripci�n: Devuelve el ultimo error ocurrido.
Precondiciones: al esta inicializado. Ocurri� un error al procesar un flujo de caracteres.
Postcondiciones: Se devuelve un c�digo de error y en mensaje un mensaje descriptivo del
mismo.*/
int TLexico_getUltimoError(TLexico* al, int codigo, char* mensaje);


#endif
