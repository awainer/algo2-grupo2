
#include "token.h"
#include "a_sintactico.h"
#include <stdio.h>



int TSintactico_Crear(TSintactico* as){
    as->error_codigo=0;
   /* as->tValidos[0]=TOKEN_OBJETO_EMPIEZA;
    as->tValidos[1]=TOKEN_ARRAY_EMPIEZA;
    as->tValidos[2]=-1;
    as->tValidos[3]=-1;
    as->tValidos[4]=-1;
    as->tValidos[5]=-1;
    as->tValidos[6]=-1;
    as->tValidos[7]=-1;
    as->tValidos[8]=-1;
    as->tValidos[9]=-1;
    as->Vtoken[OBJETO]=0;
    as->Vtoken[STRING]=0;
    as->Vtoken[NUMERO]=0;
    as->Vtoken[ARRAY]=0;
    as->Vtoken[COMA]=0;*/
    as->estado[0]=NADA;
    as->estado_idx++;

    return 0;
    }

int TSintacticoCasoValor(TSintactico * as,Token * token)

{
    switch (token->tipo)
    {
        case TOKEN_STRING:  as->estado[as->estado_idx]=VALOR;
                            TSintacticoImpimir(as, token);        /*agregar caso al switch para imprimir*/
                            return 0;
        case TOKEN_NUMERO:  as->estado[as->estado_idx]=VALOR;
                            TSintacticoImpimir(as,token);        /*agregar caso al switch para imprimir*/
                            return 0;


        case TOKEN_OBJETO_EMPIEZA:  as->estado[as->estado_idx]=OBJETO;
                                    as->estado_idx++;
                                    TSintacticoImpimir(as, token);        /*agregar caso al switch para imprimir*/
                                    return 0;

        case TOKEN_ARRAY_EMPIEZA:   as->estado[as->estado_idx]=ARRAY;
                                    as->estado_idx++;
                                    TSintacticoImpimir(as, token);        /*agregar caso al switch para imprimir*/
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
}

void TSintacticoImpimir(TSintactico * as, Token * token)
{
    switch(token->tipo)
    {
        case TOKEN_STRING : if (as->estado[as->estado_idx]==CLAVE)
                                printf("CLAVE: \"%s\"" ,token->dato);
                            else
                                printf("(String): \"%s\"" ,token->dato);
        case TOKEN_NUMERO :  printf("(Numero): \"%s\"" ,token->dato);
        case TOKEN_DOSPUNTOS: printf(" : ");
        case TOKEN_COMA: printf("\n");

        case TOKEN_OBJETO_EMPIEZA : if (as->estado[as->estado_idx-1]==NADA)
                                        printf("OBJETO\n");
                                    else
                                        printf("(Objeto): OBJETO \n");
        case TOKEN_ARRAY_EMPIEZA : if (as->estado[as->estado_idx-1]==NADA)
                                        printf("ARRAY\n");
                                    else
                                        printf("(Array): ARRAY \n");
    /*FALTAN TOKENS! */
    }
}
int TSintactico_PushToken(TSintactico* as, Token* token){
	printf("Recibo un token de tipo %d y dato %s\n",token->tipo,token->dato);

	 /*Este codigo es para debug, agregado por Ari*/



    /*la pila solo avanza cuando se inicia asi queda NADA en la pos 0 y cuando recibe un array y objeto empieza*/
    /*si vienen claves valores comas o dospuntos reescribe en la misma pos*/

	if(as->estado[as->estado_idx-1]==NADA)
	{
	    /*Estos son los tokens validos como primeros tokens */
	    if (token->tipo==TOKEN_ARRAY_EMPIEZA)
         {
            as->estado[as->estado_idx]=ARRAY;
            as->estado_idx++;
            TSintacticoImpimir(as,token);
            return 0;
         }
        else if (token->tipo==TOKEN_OBJETO_EMPIEZA)
        {
            as->estado[as->estado_idx]=OBJETO;
            as->estado_idx++;
            TSintacticoImpimir(as,token);
            return 0;
        }
        else {
            strcpy(as->error_mensaje,"Recibi un token suelto");
            as->error_codigo=1;
            return as->error_codigo;
         }

	}

if(as->estado[as->estado_idx]==OBJETO)
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


    }

                /*aca estoy trabajando domingo 3/4/11*/





    {
        strcpy(as->error_mensaje,"Se esperaba una coma");
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



	/* int i,j=0;
    int entre=0;
    while(TOKEN_NULL != token->tipo){ //esta condicion habria q cambiarla x otra q indique si termino el flujo de tokens

        switch (token->tipo){
        case TOKEN_STRING:  while (i<=3) && entre!=1)
                                if((as->tValidos[i] == token->tipo) && (as->Vtoken[STRING] == 1)){
                                    as->tValidos = [TOKEN_DOSPUNTOS];
                                    printf("clave");
                                    entre=1;
                                    }
                                else if ((as->tValidos[i] == token->tipo) && (as->Vtoken[STRING] == 2)){
                                        as->tValidos = [TOKEN_COMA,TOKEN_OBJETO_TERMINA];
                                        entre=1;
                                        printf("string")
                                }
                                    i++;
                            if(entre == 0)
                                printf(("error"));}
                            break;





        case TOKEN_NUMERO:  while ( i <= 2 )
                                if (as->tValidos[i] == token->tipo) {
                                    as->tValidos=[TOKEN_COMA]; // otra vez no estoy seguro de poner el TOKEN_NULL "dammit"
                                    //imprime el tipo aca con un printf(token->tipo) ?
                                }
                                else {
                                    i++;
                                    if (i == 3)
                                       prinft( "error" );}
                                       break;




        case TOKEN_OBJETO_EMPIEZA:   while (i<=1) && (entre!=1) && (as->Vtoken[OBJETO]==0){
                                            if(as->tValidos[i] == token->tipo){
                                                as->tValidos=[TOKEN_STRING,TOKEN_OBJETO_TERMINA];
                                                as->Vtoken[STRING]=1 //lo q significa tipo string "clave"
                                                (as->Vtoken[OBJETO])++; //incrementa en 1 lo que hay dentro de la posicion objeto cuando se abre un objeto
                                                entre=1;
                                                printf("OBJETO\n\t");
                                                T++; //incrementa la tabulacion en 1


                                            }
                                            else
                                            i++;
                                    }
                                     while (i<=7) && (entre!=1) && (as->Vtoken[OBJETO]!=0){
                                        if(as->tValidos[i] == token->tipo){
                                                as->tValidos=[TOKEN_STRING,TOKEN_OBJETO_TERMINA];
                                                as->Vtoken[STRING]=1 //lo q significa tipo string "clave"
                                                (as->Vtoken[OBJETO])++; //incrementa en 1 lo que hay dentro de la posicion objeto cuando se abre un objeto
                                                entre=1;
                                                printf("(Objeto): OBJETO\n");
                                                T=t+6; //incrementa la tabulacion en 6
                                                for (j ; j<=t ; j++){
                                                    printf(\t);         //hacer funcion tabular
                                                }
                                        else
                                        i++;
                                     if(entre == 0){
                                        printf(("error"));
                                    }
                                     break;

        case TOKEN_OBJETO_TERMINA: while (i<=3) && (entre!=1){
                                            if(as->tValidos[i] == token->tipo) && (as->Vtoken[OBJETO] == 1){
                                                printf("FIN OBJETO \n");
                                                entre==1;
                                                //solo se puede terminar el flujo
                                            }
                                            else if(as->tValidos[i] == token->tipo) && (as->Vtoken[OBJETO] != 1){
                                                as->tValidos=[TOKEN_COMA];
                                                entre=1;
                                                printf("FIN OBJETO\n");
                                                T--; //decrementa la tabulacion en 1
                                                for (j=0; j<=t; j++){
                                                    printf(\t);
                                                }
                                            }
                                        else
                                            i++;
                                    }
                                     if(entre == 0)
                                        printf(("error"));} // ver as->error_codigo
                                     break;
        case TOKEN_ARRAY_EMPIEZA,
        case TOKEN_ARRAY_TERMINA,
        case TOKEN_COMA:   while ( i <= 1 ) && (entre!=1){
                                if (as->tValidos[i] == token->tipo) && (as->Vtoken[3] == 0){
                                    as->tValidos = [TOKEN_STRING];
                                    as->Vtoken[0]=1  //osea tipo clave
                                    entre=1
                                    printf( " ,/n" );
                                else if (as->tValidos[i] == token->tipo) && (as->Vtoken[3] == 1){
                                        as->tValidos = [TOKEN_STRING];
                                        as->Vtoken[0]=2  //osea tipo string
                                        entre=1
                                        printf( " ,/n" );

                                     i++;
                                    }
                                }
                            }
                                    if (entre == 1 )
                                     printf( "error" );
                                     break;


        case TOKEN_DOSPUNTOS:  while ( i <= 1 ) && entre!=1)
                                    if (as->tValidos[i] == token->tipo) {
                                        as->tValidos = [TOKEN_STRING,TOKEN_NUMERO,TOKEN_ARRAY_EMPIEZA,TOKEN_OBJETO_EMPIEZA,TOKEN_TRUE,TOKEN_FALSE,TOKEN_NULL];  // no estoy seguro de que vaya el token_null,si va acordate de modificar el numero del while
                                        as->Vtoken[STRING]=2;     //lo q significa tipo de string "string"
                                        entre=1;
                                        printf( " : " ) ;}
                                    else
                                        i++;
                                     if (entre == 0)
                                     printf( "error" ) ; // ver as->error_codigo
                                     break;

        case TOKEN_TRUE,
        case TOKEN_FALSE,

        if (as->Vtoken[6]=1)
            if (as->Vtoken[5]=1)
                printf("sali bien")
            else
                printf("sali mal");


*/


  return 0;
    }


int TSintactico_terminarFlujo(TSintactico* as){
    return 0;
    }



int TSintactico_getUltimoError(TSintactico*  as, int *codigo, char* mensaje){
    return 0;
    }
