
#include "token.h"
#include "a_sintactico.h"
#include <stdio.h>



int TSintactico_Crear(TSintactico* as){
    as->error_codigo=0;
    as->tValidos[0]=TOKEN_OBJETO_EMPIEZA;
    as->tValidos[1]=TOKEN_NULL;
    as->Vtoken[OBJETO]=0;
    as->Vtoken[STRING]=0;
    as->Vtoken[NUMERO]=0;
    as->Vtoken[ARRAY]=0;
    as->Vtoken[COMA]=0;
    return 0;
    }

int TSintactico_PushToken(TSintactico* as, Token* token){

	/* Este codigo es para debug, agregado por Ari*/
	printf("Recibo un token de tipo %d y dato %s\n",token->tipo,token->dato);
	return 0;



	/* int i=0;
    int entre=0;
    while(TOKEN_NULL != token->tipo){
        as->Vtoken[6]=0;
        switch (token->tipo){
        case TOKEN_STRING:  while (i<=3) || entre!=1)
                                if((as->tValidos[i] == token->tipo) && (as->Vtoken[STRING] == 1)){
                                    as->tValidos = [TOKEN_DOSPUNTOS,TOKEN_NULL];  //el token null habria que sacarlo porque al ser null termina y queda algo incorrecto sintacticamente.
                                    printf("clave");                               // en los tvalidos habria que agregar el token_coma
                                    entre=1;
                                    }
                                else if ((as->tValidos[i] == token->tipo) && (as->Vtoken[0] == 2)){
                                        as->tValidos = [TOKEN_COMA,TOKEN_NULL];
                                        entre=1;
                                        printf("string")
                                }
                                    i++;
                            if(i entre == 0)
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




        case TOKEN_OBJETO_EMPIEZA:   while (i<=3) || (entre!=1){
                                            if(as->tValidos[i] == token->tipo){
                                                as->tValidos=[TOKEN_OBJETO_TERMINA,TOKEN_STRING,TOKEN_NULL];
                                                as->Vtoken[STRING]=1 lo q significa tipo string "clave"
                                                as->Vtoken[OBJETO]++; incrementa en 1 cuando se abre un objeto
                                                entre=1;
                                                printf("OBJETO\n\t");

                                                // ¿Aca deberia imprimir el token ademas de escribir objeto?
                                            }
                                        else
                                            i++;
                                    }
                                     if(entre == 0)
                                        printf(("error"));} // ver as->error_codigo
                                     break;

        case TOKEN_OBJETO_TERMINA: as->tValidos=[TOKEN_NULL] ; // si termina el objeto ya no puede venir ningun otro
                                   as->Vtoken[5]=1;
                                   printf( "FIN OBJETO\n\t);
                                   break; // aca imagino que deberia mandar algo a tsintactico_terminar_flujo

        case TOKEN_ARRAY_EMPIEZA,
        case TOKEN_ARRAY_TERMINA,
        case TOKEN_COMA:   while ( i <= 1 ) || (entre!=1){
                                if (as->tValidos[i] == token->tipo) && (as->Vtoken[3] == 0){
                                    as->tValidos = [TOKEN_STRING];
                                    as->Vtoken[0]=1 /* osea tipo clave
                                    entre=1
                                    printf( " ,/n" );
                                else if (as->tValidos[i] == token->tipo) && (as->Vtoken[3] == 1){
                                        as->tValidos = [TOKEN_STRING];
                                        as->Vtoken[0]=2 /* osea tipo string
                                        entre=1
                                        printf( " ,/n" );

                                     i++;
                                    }
                                }
                            }
                                    if (entre == 1 )
                                     printf( "error" );
                                     break;


        case TOKEN_DOSPUNTOS:  while ( i <= 1 ) || entre!=1)
                                    if (as->tValidos[i] == token->tipo) {
                                        as->tValidos = [TOKEN_STRING,TOKEN_NUMERO,TOKEN_ARRAY_EMPIEZA,TOKEN_OBJETO_EMPIEZA,];  // no estoy seguro de que vaya el token_null,si va acordate de modificar el numero del while
                                        as->Vtoken[STRING]=2;     /*lo q significa tipo de string "string"
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
