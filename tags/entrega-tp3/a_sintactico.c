

#include "token.h"
#include "a_sintactico.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include "Pila.h"
#define TamanioDato sizeof(int)

int Tsintactico_setCallback(TSintactico *ts, int evento, void* tda_contexto, int(*callback)(  void  *,  void*) )
{
   ts->arrayCallbacks[evento].cb=callback;
   ts->arrayCallbacks[evento].contexto=tda_contexto;
   return 0;
}



int TSintactico_Crear(TSintactico* as){
    as->error_codigo=0;
    P_Crear(&as->pP, sizeof(TipoEstado));

    /*Seteo la callback para cada evento */
    /*Tsintactico_setCallback(as,CB_COMIENZA_ARRAY,as->constructor,Tconstructor_eventoComienzaArray);
    Tsintactico_setCallback(as,CB_TERMINA_ARRAY,as->constructor,Tconstructor_eventoTerminaArray);
    Tsintactico_setCallback(as,CB_COMIENZA_OBJETO,as->constructor,Tconstructor_eventoComienzaObjeto);
    Tsintactico_setCallback(as,CB_TERMINA_OBJETO,as->constructor,Tconstructor_eventoTerminaObjeto);
    Tsintactico_setCallback(as,CB_CLAVE,as->constructor,Tconstructor_eventoClave);
    Tsintactico_setCallback(as,CB_TRUE,as->constructor,Tconstructor_eventoTrue);
    Tsintactico_setCallback(as,CB_FALSE,as->constructor,Tconstructor_eventoFalse);
    Tsintactico_setCallback(as,CB_NULL,as->constructor,Tconstructor_eventoNull);
    Tsintactico_setCallback(as,CB_NUMERO,as->constructor,Tconstructor_eventoNumero);
    Tsintactico_setCallback(as,CB_STRING,as->constructor,Tconstructor_eventoString);*/

    return 0;
    }

int TSintacticoCasoValor(TSintactico * as,Token * token){
char nada[2];
    switch (token->tipo){
		case TOKEN_STRING:

                            as->estado=VALOR;
                            return as->arrayCallbacks[CB_STRING].cb(as->arrayCallbacks[CB_STRING].contexto,(void*)token->dato );
                            /*return 0;*/
		case TOKEN_NUMERO:  as->estado=VALOR;
                            return as->arrayCallbacks[CB_NUMERO].cb(as->arrayCallbacks[CB_NUMERO].contexto,(void*)token->dato );
                            /*return 0;*/


		case TOKEN_OBJETO_EMPIEZA:  as->estpila=OBJETO;
                                    as->estado=OBJETO;
                                    P_Poner(&as->pP, (void*)&as->estpila);
                                    return as->arrayCallbacks[CB_COMIENZA_OBJETO].cb(as->arrayCallbacks[CB_COMIENZA_OBJETO].contexto, (void*)nada);
                                    /*return 0;*/

		case TOKEN_ARRAY_EMPIEZA:   as->estpila=ARRAY;
                                    as->estado=ARRAY;
                                    P_Poner(&as->pP, (void*)&as->estpila);
                                    return as->arrayCallbacks[CB_COMIENZA_ARRAY].cb(as->arrayCallbacks[CB_COMIENZA_ARRAY].contexto,(void*)nada );
                                    /*return 0;*/
		case TOKEN_TRUE:            as->estado=VALOR;
                                    return as->arrayCallbacks[CB_TRUE].cb(as->arrayCallbacks[CB_TRUE].contexto, (void*)nada);
                                    /*return 0;*/
		case TOKEN_FALSE:           as->estado=VALOR;
                                    return as->arrayCallbacks[CB_FALSE].cb(as->arrayCallbacks[CB_FALSE].contexto, (void*)nada );
                                    /*return 0;*/

		case TOKEN_NULL:            as->estado=VALOR;
                                    return as->arrayCallbacks[CB_NULL].cb(as->arrayCallbacks[CB_NULL].contexto, (void*)nada );
                                    /*return 0;*/
		default : { strcpy(as->error_mensaje,"se esperaba un valor");
                as->error_codigo=E_SINTACTICO;
                return as->error_codigo; }

    }
    return 0;
}



int TSintactico_PushToken(TSintactico* as, Token* token)
{


/*si la pila esta vacia se ejecuta este if*/
char nada[2];

/*printf("Recibo un token de tipo %d y dato %s\n",token->tipo,token->dato);*/

if (P_Vacia(as->pP))
{
    if (token->tipo==TOKEN_ARRAY_EMPIEZA)
    {
        as->estpila=ARRAY;
        as->estado=ARRAY;
        P_Poner(&as->pP,&as->estpila);
        return as->arrayCallbacks[CB_COMIENZA_ARRAY].cb(as->arrayCallbacks[CB_COMIENZA_ARRAY].contexto, (void*)nada);
        /*return 0;*/
    }
    else if (token->tipo==TOKEN_OBJETO_EMPIEZA)
    {
        as->estpila=OBJETO;
        as->estado=OBJETO;
        P_Poner(&as->pP, (void*)&as->estpila);
        return as->arrayCallbacks[CB_COMIENZA_OBJETO].cb(as->arrayCallbacks[CB_COMIENZA_OBJETO].contexto, (void*)nada);
        /*return 0;*/

    }
    else
    {

        strcpy(as->error_mensaje,"Recibi un token suelto");
        as->error_codigo=E_SINTACTICO;
        Tsintactico_Destruir(as);
        return as->error_codigo;
    }
}

/*pila no vacia*/
else
{
    if (as->estpila==OBJETO)
    {
        if (as->estado==OBJETO) /*si lo ultimo abierto fue un objeto viene una clave o cierre de objeto*/
        {
            if (token->tipo==TOKEN_STRING)
            {
                as->estado=CLAVE; /*Cambio CB_STRING a CB_CLAVE, creo que es lo correcto. Ari. */
                return as->arrayCallbacks[CB_CLAVE].cb(as->arrayCallbacks[CB_CLAVE].contexto,(void*)token->dato );
                /*return 0;*/
            }
            else if (token->tipo==TOKEN_OBJETO_TERMINA)
            {
                P_Sacar(&as->pP, (void*)&as->estpila);
                as->arrayCallbacks[CB_TERMINA_OBJETO].cb(as->arrayCallbacks[CB_TERMINA_OBJETO].contexto, (void*)nada );
                if(P_Vacia(as->pP))        /*si la pila esta vacia termino el flujo*/
                    return 0;
                else
                {
                    P_Sacar(&as->pP, (void*)&as->estpila);
                    P_Poner(&as->pP, (void*)&as->estpila);
                    if(as->estpila==OBJETO)
                    {
                        as->estado=VALOR;
                        return 0;
                    }
                    else        /*la unica que queda es q halla un array en la pila*/
                    {
                        as->estado=VALOR;
                        return 0;
                    }
                }
            }
            else
            {
                strcpy(as->error_mensaje,"se esperaba clave o obj termina");
                as->error_codigo=E_SINTACTICO;
                Tsintactico_Destruir(as);
                return as->error_codigo;
            }

        }
        else if (as->estado==CLAVE) /*si lo ultimo fue una clave ahora viene un dospuntos*/
        {
            if (token->tipo==TOKEN_DOSPUNTOS)
            {
                as->estado=DOSP;
                return 0;
            }
            else
            {
                strcpy(as->error_mensaje,"se esperaba un dospuntos");
                as->error_codigo=E_SINTACTICO;
                Tsintactico_Destruir(as);
                return as->error_codigo;
            }
        }
        else if (as->estado==DOSP)  /*si lo ultimo fue un dosp ahora viene un valor*/
        {
            TSintacticoCasoValor(as,token);
            return 0;
        }
        else if (as->estado==VALOR) /*ultimo recibido un valor ahora viene una coma o un fin de objeto*/
        {
            if (token->tipo==TOKEN_COMA)
            {
                as->estado=COMA;
                return 0;
            }
            else if (token->tipo==TOKEN_OBJETO_TERMINA)
            {
                P_Sacar(&as->pP, (void*)&as->estpila);
                as->arrayCallbacks[CB_TERMINA_OBJETO].cb(as->arrayCallbacks[CB_TERMINA_OBJETO].contexto , (void*)nada);
                if(P_Vacia(as->pP))        /*si la pila esta vacia termino el flujo*/
                    return 0;
                else
                {
                    P_Sacar(&as->pP, (void*)&as->estpila);
                    P_Poner(&as->pP, (void*)&as->estpila);
                    if(as->estpila==OBJETO)
                    {
                        as->estado=VALOR;
                        return 0;
                    }
                    else        /*la unica que queda es q halla un array en la pila*/
                    {
                        as->estado=VALOR;
                        return 0;
                    }
                }

            }
            else
            {
                strcpy(as->error_mensaje,"se esperaba una coma, un fin de obj o fin de array");
                as->error_codigo=E_SINTACTICO;
/*                Tsintactico_Destruir(as);*/
                return as->error_codigo;
            }

            return 0;
        }
        else if(as->estado==COMA)    /*si lo ultimo fue una coma ahora viene una clave*/
        {
            if (token->tipo==TOKEN_STRING)
            {
                as->estado=CLAVE; /*Cambio aca tambien. Ari */
                as->arrayCallbacks[CB_CLAVE].cb(as->arrayCallbacks[CB_CLAVE].contexto,(void*)token->dato );
                return 0;
            }
            else
            {
                strcpy(as->error_mensaje,"se esperaba una clave");
                as->error_codigo=E_SINTACTICO;
                Tsintactico_Destruir(as);
                return as->error_codigo;
            }
        }
    }
    else if(as->estpila==ARRAY)
    {
        if(as->estado==ARRAY)   /*si abri un array viene cierre de array o un valor*/
        {
            if (token->tipo==TOKEN_ARRAY_TERMINA)
            {
                P_Sacar(&as->pP, (void*)&as->estpila);
                as->arrayCallbacks[CB_TERMINA_ARRAY].cb(as->arrayCallbacks[CB_TERMINA_ARRAY].contexto , (void*)nada);
                if(P_Vacia(as->pP))        /*si la pila esta vacia termino el flujo*/
                    return 0;
                else
                {
                    P_Sacar(&as->pP, (void*)&as->estpila);
                    P_Poner(&as->pP, (void*)&as->estpila);
                    if(as->estpila==OBJETO)
                    {
                        as->estado=VALOR;
                        return 0;
                    }
                    else        /*la unica que queda es q halla un array en la pila*/
                    {
                        as->estado=VALOR;
                        return 0;
                    }
                }
            }
            else
            {
                TSintacticoCasoValor(as,token);
                return 0;
            }
        }
        else if(as->estado==VALOR)  /*estoy en valor espero una coma o un fin de array*/
        {
            if (token->tipo==TOKEN_COMA)
            {
                as->estado=COMA;
                return 0;
            }
            else if (token->tipo==TOKEN_ARRAY_TERMINA)
            {
                P_Sacar(&as->pP, (void*)&as->estpila);
                as->arrayCallbacks[CB_TERMINA_ARRAY].cb(as->arrayCallbacks[CB_TERMINA_ARRAY].contexto, (void*)nada);
                if(P_Vacia(as->pP))        /*si la pila esta vacia termino el flujo*/
                    return 0;
                else
                {
                    P_Sacar(&as->pP, (void*)&as->estpila);
                    P_Poner(&as->pP, (void*)&as->estpila);
                    if(as->estpila==OBJETO)
                    {
                        as->estado=VALOR;
                        return 0;
                    }
                    else        /*la unica que queda es q halla un array en la pila*/
                    {
                        as->estado=VALOR;
                        return 0;
                    }
                }
            }
            else
            {
                strcpy(as->error_mensaje,"se esperaba una coma o un fin de array");
                as->error_codigo=E_SINTACTICO;
                Tsintactico_Destruir(as);
                return as->error_codigo;
            }
        }
        else if(as->estado==COMA) /*si lo ultimo fue una coma ahora viene un valor*/
        {
            TSintacticoCasoValor(as,token);
            return 0;
        }
        else
            {
                strcpy(as->error_mensaje,"se esperaba una valor");
                as->error_codigo=E_SINTACTICO;
                Tsintactico_Destruir(as);
                return as->error_codigo;
            }
    }


}
return as->error_codigo;
}



int TSintactico_terminarFlujo(TSintactico* as)
{

	if (P_Vacia(as->pP))
		{
		    TSintactico_Crear(as);          /*Se reinició el TDA para procesar otro flujo. */
		    return 0;
		}
	else
	{
	    strcpy(as->error_mensaje,"Fin de flujo antes de cerrar todos los scopes");  /* De haberse terminado el flujo en estado inconsistente, devuelve mensaje del error. */
	    as->error_codigo=E_SINTACTICO;
        return as->error_codigo;
	}


    return 0;
}



int TSintactico_getUltimoError(TSintactico*  as, int *codigo, char* mensaje){

    *codigo=as->error_codigo;
    strcpy(mensaje,as->error_mensaje);
    return 0;
    }


int Tsintactico_Destruir(TSintactico* as){

P_Vaciar(&as->pP);

return 0;
}









/*
int TSintactico_setCallback (TSintactico *ts, int evento, void* tda_contexto, int(*callback)(const void*, int, const void*)){

return NULL; */
