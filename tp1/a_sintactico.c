

#include "token.h"
#include "a_sintactico.h"
#include <stdio.h>
#include <string.h>



int TSintactico_Crear(TSintactico* as){
    as->error_codigo=0;
    as->estado[0]=NADA;
    as->estado_idx=1;

    return 0;
    }

int TSintacticoCasoValor(TSintactico * as,Token * token){

    switch (token->tipo){
		case TOKEN_STRING:  as->estado[as->estado_idx]=VALOR;
                            TSintacticoImpimir(as, token);        /*agregar caso al switch para imprimir*/
                            return 0;
		case TOKEN_NUMERO:  as->estado[as->estado_idx]=VALOR;
                            TSintacticoImpimir(as,token);        /*agregar caso al switch para imprimir*/
                            return 0;


		case TOKEN_OBJETO_EMPIEZA:  as->estado[as->estado_idx]=OBJETO;
                                    TSintacticoImpimir(as, token);        /*agregar caso al switch para imprimir*/
                                    as->estado_idx++;
                                    return 0;

		case TOKEN_ARRAY_EMPIEZA:   as->estado[as->estado_idx]=ARRAY;
                                    TSintacticoImpimir(as, token);        /*agregar caso al switch para imprimir*/
                                    as->estado_idx++;
                                    return 0;
		case TOKEN_TRUE:           as->estado[as->estado_idx]=VALOR;
                                    TSintacticoImpimir(as,token);        /*agregar caso al switch para imprimir*/
                                    return 0;
		case TOKEN_FALSE:         as->estado[as->estado_idx]=VALOR;
                                    TSintacticoImpimir(as,token);        /*agregar caso al switch para imprimir*/
                                    return 0;

		case TOKEN_NULL:         as->estado[as->estado_idx]=VALOR;
                                    TSintacticoImpimir(as,token);        /*agregar caso al switch para imprimir*/
                                    return 0;
		default : { strcpy(as->error_mensaje,"se esperaba un valor");
                as->error_codigo=1;
                return as->error_codigo; }

    }
    return 0;
}

int TSintacticoImpimir(TSintactico * as, Token * token){

	switch(token->tipo)
    {
        case TOKEN_STRING : if (as->estado[as->estado_idx]==CLAVE)
                                printf("CLAVE: \"%s\"" ,token->dato);
                            else
                                printf("(String): \"%s\"" ,token->dato);
                            return 0;

        case TOKEN_NUMERO :  printf("(Numero): \"%s\"" ,token->dato);
                            return 0;

        case TOKEN_DOSPUNTOS: printf(" : ");
                            return 0;

        case TOKEN_COMA: printf("\n");
                            return 0;
        case TOKEN_OBJETO_EMPIEZA : if (as->estado[as->estado_idx-1]==NADA)
                                        printf("OBJETO\n");
                                    else
                                        printf("(Objeto): OBJETO \n");
                            return 0;

        case TOKEN_ARRAY_EMPIEZA : if (as->estado[as->estado_idx-1]==NADA)
                                        printf("ARRAY\n");
                                    else
                                        printf("(Array): ARRAY \n");
                                   return 0;

        case TOKEN_TRUE :  printf(" (boolean): TRUE \n");
                            return 0;
        case TOKEN_FALSE : printf(" (boolean) : FALSE \n");
                            return 0;
        case TOKEN_NULL : printf(" (Null) :    \n ");
                            return 0;
        case TOKEN_ARRAY_TERMINA: printf( " FIN ARRAY \n " );
                            return 0;
        case TOKEN_OBJETO_TERMINA: printf( " FIN OBJETO \n ");
                            return 0;
        default : return 1;
    }
}

int TSintactico_PushToken(TSintactico* as, Token* token){
/*	printf("Recibo un token de tipo %d y dato %s\n",token->tipo,token->dato);*/

	 /*Este codigo es para debug, agregado por Ari*/



    /*la pila solo avanza cuando se inicia asi queda NADA en la pos 0 y cuando recibe un array y objeto empieza*/
    /*si vienen claves valores comas o dospuntos reescribe en la misma pos*/

	if(as->estado[as->estado_idx-1]==NADA)
	{
	    /*Estos son los tokens validos como primeros tokens */
	    if (token->tipo==TOKEN_ARRAY_EMPIEZA)
         {
            as->estado[as->estado_idx]=ARRAY;
            TSintacticoImpimir(as,token);
            as->estado_idx++;
            return 0;
         }
        else if (token->tipo==TOKEN_OBJETO_EMPIEZA)
        {
            as->estado[as->estado_idx]=OBJETO;
            TSintacticoImpimir(as,token);
            as->estado_idx++;
            return 0;
        }
        else {
            strcpy(as->error_mensaje,"Recibi un token suelto");
            as->error_codigo=1;
            return as->error_codigo;
         }

	}

if(as->estado[as->estado_idx-1]==OBJETO)
{
    /*Estos son los tokens validos si lo ultimo que hize fue abrir un objeto */
    if(token->tipo==TOKEN_STRING)
       {
           /*esto es una clave*/
           as->estado[as->estado_idx]=CLAVE;
           TSintacticoImpimir(as, token); /*llamar a otra funcion para imprimir tipo clave*/
           return 0;
       }
    else
       {
          strcpy(as->error_mensaje,"Se esperaba una clave");
          as->error_codigo=1;
          return as->error_codigo;
       }
}
/* Si lo ultimo recibido fue una clave, ahora tengo que recibir un dospuntos*/
if(as->estado[as->estado_idx]==CLAVE)
{
    if(token->tipo==TOKEN_DOSPUNTOS)
    {
      as->estado[as->estado_idx]=DOSP;
      TSintacticoImpimir(as,token);        /*agregar caso al switch*/
      return 0;
    }
    else
    {
        strcpy(as->error_mensaje,"Se esperaba dos puntos");
        as->error_codigo=1;
        return as->error_codigo;
    }
}
/* Si lo ultimo recibido fue un array, ahora tengo que recibir un valor*/
 if (as->estado[as->estado_idx-1]== ARRAY)
{
     TSintacticoCasoValor(as,token);
}
/*si lo ultimo recibido fue un dospuntos , ahora tengo q recibir un valor*/
 if (as->estado[as->estado_idx]== DOSP)
{
     TSintacticoCasoValor(as,token);
}
 /*si lo ultimo recibido fue un valor, ahora tengo q recibir una coma o un fin de objeto o fin de array respectivamente*/
 if (as->estado[as->estado_idx]== VALOR)
 {
     if(token->tipo==TOKEN_COMA)
    {
        as->estado[as->estado_idx]=COMA;
        TSintacticoImpimir(as,token);        /*agregar caso al switch*/
        return 0;
    }
    else if ((token->tipo==TOKEN_OBJETO_TERMINA) && (as->estado[as->estado_idx-1]== OBJETO))
    {

        TSintacticoImpimir(as,token);
        as->estado_idx--;                                   /* si viene un objeto_cierra, y antes tenia un objeto, entonces vuelvo una posicion */
        if (as->estado[as->estado_idx-1]== ARRAY)           /*si antes tenia un array entonces estaba en un valor*/
        {
            as->estado[as->estado_idx]=VALOR;

            return 0;
        }
        else if (as->estado[as->estado_idx-1]== OBJETO)         /*y sino estaba en un objeto osea que tmb estaba en un valor */
        {
            as->estado[as->estado_idx]=VALOR;

            return 0;
        }
        else    /*el estado anterior era NADA entonces todo lo q se abrio se cerro*/
        {
            as->estado[as->estado_idx]=NADA;

            return 0;

        }
    }
    else if ((token->tipo==TOKEN_ARRAY_TERMINA) && (as->estado[as->estado_idx-1]== ARRAY))
    {
        as->estado_idx--;
        if (as->estado[as->estado_idx-1]== ARRAY)           /*si antes tenia un array entonces estaba en un valor*/
        {
            as->estado[as->estado_idx]=VALOR;

            return 0;
        }
        else if (as->estado[as->estado_idx-1]== OBJETO)      /*y sino estaba en un objeto osea que tmb estaba en un valor */
        {
            as->estado[as->estado_idx]=VALOR;

            return 0;
        }
        else    /*el estado anterior era NADA entonces todo lo q se abrio se cerro*/
        {
            as->estado[as->estado_idx]=NADA;

            return 0;
        }

    }
    else
    {
        strcpy(as->error_mensaje,"Se esperaba una coma, un fin de array o un fin de objeto");
        as->error_codigo=1;
        return as->error_codigo;
    }
 }

 /*si lo ultimo recibido fue una coma, ahora tengo q recibir una clave o un valor depende si estaba en un objeto o en un array*/
 if (as->estado[as->estado_idx]== COMA)
 {
     if (as->estado[(as->estado_idx-1)]==OBJETO)
     {
         if(token->tipo==TOKEN_STRING)
       {
           /*esto es una clave*/
           as->estado[as->estado_idx]=CLAVE;
           TSintacticoImpimir(as, token); /*llamar a otra funcion para imprimir tipo clave*/
           return 0;
       }
        else
       {
          strcpy(as->error_mensaje,"Se esperaba una clave");
          as->error_codigo=1;
          return as->error_codigo;
       }
     }
     else if (as->estado[(as->estado_idx-1)]==ARRAY)
     {
         TSintacticoCasoValor(as,token);
     }
 }
	return 0;

    }


int TSintactico_terminarFlujo(TSintactico* as){
	/*fclose(archivo);  *- Se cierra el documento .JSON con el que estabamos trabajando.
					    - La variable archivo es un puntero a archivo (FALTA DECLARARLO).
						*
	if (as->error_codigo == 1)             * De haberse terminado el flujo en estado inconsistente, devuelve mensaje del error. *
		printf("ERROR DE SINTAXIS");
	else if (as->error_codigo==NADA)
            printf("TERMINE BIEN");


	int TSintactico_Crear(as);
	 *Se reinició el TDA para procesar otro flujo. */

    return 0;
    }



int TSintactico_getUltimoError(TSintactico*  as, int *codigo, char* mensaje){
    return 0;
    }
