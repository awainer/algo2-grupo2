
#include "token.h"
#include "a_sintactico.h"




int TSintactico_Crear(TSintactico* as){
    as->error_codigo=0;
    as->tValidos[0]=TOKEN_OBJETO_EMPIEZA;
    as->tValidos[1]=TOKEN_NULL;
    as->Vtoken[TOKEN_STRING,TOKEN_NUMERO,TOKEN_ARRAY_EMPIEZA,TOKEN_COMA];
    return 0;
    }

int TSintactico_PushToken(TSintactico* as, Token* token){
   /* int i=0;
    while(TOKEN_NULL != token->tipo){
        switch (token->tipo){
        case TOKEN_STRING:  while (i<=2)
                                if((as->tValidos[i] == token->tipo) && (as->Vtoken[TOKEN_STRING] == 1)){
                                    as->tValidos = [TOKEN_DOSPUNTOS,TOKEN_NULL];  //el token null habria que sacarlo porque al ser null termina y queda algo incorrecto sintacticamente.
                                    printf("clave");                               // en los tvalidos habria que agregar el token_coma
                                    as->Tstring = 2;
                                    }
                                    else {
                                        i++;
                            if(i == 2)
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




        case TOKEN_OBJETO_EMPIEZA:   while (i<=1)
                                            if(as->tValidos[i] == token->tipo){
                                                as->tValidos=[TOKEN_OBJETO_TERMINA,TOKEN_STRING,TOKEN_NULL];
                                                printf("OBJETO\n\t");
                                                // ¿Aca deberia imprimir el token ademas de escribir objeto?
                                            }
                                        else {
                                            i++;
                                     if(i == 2)
                                        printf(("error"));} // ver as->error_codigo
                                     break;

        case TOKEN_OBJETO_TERMINA: as->tValidos=[TOKEN_NULL] ; // si termina el objeto ya no puede venir ningun otro
                                   printf( "FIN OBJETO\n\t);
                                   break; // aca imagino que deberia mandar algo a tsintactico_terminar_flujo

        case TOKEN_ARRAY_EMPIEZA,
        case TOKEN_ARRAY_TERMINA,
        case TOKEN_COMA:   while ( i <= 1 )
                                if (as->tValidos[i] == token->tipo) {
                                    as->tValidos = [TOKEN_STRING,TOKEN_NUMERO];
                                    printf( " , " );
                                }
                                else {
                                     i++;
                                     if ( i == 2 )
                                     printf( "error" ); }
                                     break;


        case TOKEN_DOSPUNTOS:  while ( i <= 1 )
                                    if (as->tValidos[i] == token->tipo) {
                                        as->tValidos = [TOKEN_STRING,TOKEN_NUMERO,TOKEN_ARRAY_EMPIEZA];  // no estoy seguro de que vaya el token_null,si va acordate de modificar el numero del while
                                        printf( " : " ) ;}
                                    else
                                        i++;
                                     if (i == 2)
                                     printf( "error" ) ; // ver as->error_codigo
                                     break;

        case TOKEN_TRUE,
        case TOKEN_FALSE,


*/

    return 0;
    }


int TSintactico_terminarFlujo(TSintactico* as){
    return 0;
    }



int TSintactico_getUltimoError(TSintactico*  as, int *codigo, char* mensaje){
    return 0;
    }
