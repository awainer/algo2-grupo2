#ifndef A_SINTACTICO_H_INCLUDED
#define A_SINTACTICO_H_INCLUDED
#include "Pila.h"
#include "token.h"
#include "constr_tweets.h"
typedef enum
{
    /*enumerado de callbacks*/
    CB_COMIENZA_ARRAY,
    CB_TERMINA_ARRAY,
    CB_COMIENZA_OBJETO,
    CB_TERMINA_OBJETO,
    CB_CLAVE,
    CB_TRUE,
    CB_FALSE,
    CB_NULL,
    CB_NUMERO,
    CB_STRING
} evento;
typedef enum
{
    /*enumerado para manejarnos dentro de la pseudopila para soportar los anidamientos*/
    NADA,
    OBJETO,
    CLAVE,
    VALOR,
    ARRAY,
    DOSP,
    COMA
} TipoEstado;

typedef struct tda_sintactico
{
    /* El ultimo error recibido, 0 es ok. */
    int  error_codigo;
    char error_mensaje[30];
    /*una variable donde guardare los estados q no irian en la pila(clave valor etc)*/
    int  estado;
    /*guardo los estados antes de ponerlos en la pila(objeto array)*/
    int estpila;
    TPila   pP;
    /*evento * callbacks[10];*/
    void (*callbacks[10]) (Tconstructor * tc, void * dato);
    Tconstructor * constructor;
    /* comento esto para mostrar mi idea
     Estos son los tokens validos como clave
       TipoToken tValidos[4]; indica los tokens validos que pueden venir. nose x q lo borraron
    int Vtoken[4];  indica en que situacion estoy con un flag en el token adecuado*/

} TSintactico;




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
mismo.
*/
int TSintactico_getUltimoError(TSintactico*  as, int *codigo, char* mensaje);

/*
Descripción: Forma de comunicarse con el exterior. Se establece ante la ocurrencie del evento "evento". De haber sido definida previamente se reemplaza
por esta nueva.
Precondiciones: ts ha sido creado.
Postcondiciones: se establece la callback a llamar ante la ocurrencia del evento "evento". Si ya se había definido la callback se reemplaza por esta
nueva.
*/
int TSintactico_setCallback (TSintactico *ts, int evento, void* tda_contexto, int(*callback)(const void*, int, const void*));



int TSintacticoImpimir(TSintactico * as, Token * token);

/*int Tsintactico_setCallback(TSintactico *ts, int evento, void* tda_contexto, void(*callback)(const void*, const void*));*/
#endif
