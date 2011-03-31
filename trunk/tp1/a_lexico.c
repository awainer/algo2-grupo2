/*Implementaciones del TDA TLexico*/

#include "a_lexico.h"
#include <string.h>
#include <stdio.h>

int TLexico_Crear(TLexico* al)
{
    al->error_codigo=0;
    al->buffer_idx=-1;
    al->token.tipo=TOKEN_NULL;

    return 0;
}

int TLexico_setAnalizadorSintactico(TLexico* al, TSintactico* as)
{
    al-> sintactico = as;
    return 0;
}

int Tlexico_push_token(TLexico * al, TSintactico * ts)
{
    /* Esta es la funcion que llama TLexico_PushChar cuando armo un token listo para mandar */
if (TSintactico_PushToken(al->sintactico,&al->token)==0)
            {
                /* Reseteo el token*/
                al->token.tipo=TOKEN_NULL;
                al->buffer_idx=-1;
                al->token.dato[0]=0;
                return 0;
            }

            else
            {
                al->error_codigo=1;
                strcpy(al->error_mensaje,"El asintactico me devolvio error");
                return 1;
           }

}

void tlexico_acumular_dato(TLexico * al, char c)
{
    /*Esta funcion concatena un caracter al dato del token de un TLexico */
    al->buffer_idx++;
    al->token.dato[al->buffer_idx]=c;
    al->token.dato[al->buffer_idx+1]=0;
}

int TLexico_PushChar(TLexico* al, char c)
{
    /*Recibo comillas*/
    if (c=='"')
    {
        if (al->buffer_idx==-1)
        {
            /* Si recibo una comilla pero el indice esta en -1,
            significa que comienza un string*/
            al->token.tipo=TOKEN_STRING;
            /*   al->buffer_idx++;*/
            return 0;
        }
        else
        {
            /* Si recibo una comilla con el indice distinto de -1,
            tengo que terminar el string y resetear */
            return Tlexico_push_token(al,al->sintactico);
        }

    } /* fin recibo comillas */


/*Recibo numeros sin estar dentro de un token, empiezo a juntar numeros*/
if ((al->token.tipo==TOKEN_NULL) && (c>='0') && (c<='9') )
{
    al->token.tipo=TOKEN_NUMERO;
    tlexico_acumular_dato(al,c);
    return 0;
}

/*Recibo numeros ya dentro de un token*/
if (al->token.tipo==TOKEN_NUMERO)
{
     if( (c>='0') && (c<='9') ){
        tlexico_acumular_dato(al,c);
        return 0;
    }
    if((c==' ' ) || (c=='\t')) /*Un espacio o tab termina un numero */
    {
    return Tlexico_push_token(al,al->sintactico);
    }

    if(c==',')
    /*Esto no esta muy bueno asi, pero no se me ocurre una forma mejor
    porque cuando recibo una coma en medio de un numero, tengo que mandar 2 tokens */
    {
        if(Tlexico_push_token(al,al->sintactico)==0)
        {
         al->token.tipo=TOKEN_COMA;
         return Tlexico_push_token(al,al->sintactico);
        }
        else
        {
            al->error_codigo=1;
            strcpy(al->error_mensaje,"El asintactico me devolvio error");
            return 1;
        }
    }
    else if(c==']')
    /*Esto no esta muy bueno asi, pero no se me ocurre una forma mejor
    porque cuando recibo una coma en medio de un numero, tengo que mandar 2 tokens */
    {
        if(Tlexico_push_token(al,al->sintactico)==0)
        {
         al->token.tipo=TOKEN_ARRAY_TERMINA;
         return Tlexico_push_token(al,al->sintactico);
        }
        else
        {
            al->error_codigo=1;
            strcpy(al->error_mensaje,"El asintactico me devolvio error");
            return 1;
        }
    }
    else if(c=='}')
    /*Esto no esta muy bueno asi, pero no se me ocurre una forma mejor
    porque cuando recibo una coma en medio de un numero, tengo que mandar 2 tokens */
    {
        if(Tlexico_push_token(al,al->sintactico)==0)
        {
         al->token.tipo=TOKEN_OBJETO_TERMINA;
         return Tlexico_push_token(al,al->sintactico);
        }
        else
        {
            al->error_codigo=1;
            strcpy(al->error_mensaje,"El asintactico me devolvio error");
            return 1;
        }
    }
    else{

        al->error_codigo=1;
        strcpy(al->error_mensaje,"Caracter inesperado en medio de un numero");
        return 1;
    }
}

/*Estamos juntando un string */
if (al->token.tipo==TOKEN_STRING)
{

    if ( (( c >= 'a' )&&( c <= 'z' ) ) || ( (c>='A') && (c<='Z') ) || (c==' ') || (c =='\t') || ( (c>='0') && (c<='9')  )   )
    {
        tlexico_acumular_dato(al,c);
        return 0;
    }
    else
    {
      		al->error_codigo=1;
       		strcpy(al->error_mensaje,"Recibi un caracter no valido dentro de un string");
       		return al->error_codigo;
    }
}

/*Estos son los tokens "atomicos" */

if(c=='{')
    al->token.tipo=TOKEN_OBJETO_EMPIEZA;
else if(c=='}')
    al->token.tipo=TOKEN_OBJETO_TERMINA;
else if(c=='[')
    al->token.tipo=TOKEN_ARRAY_EMPIEZA;
else if(c==']')
    al->token.tipo=TOKEN_ARRAY_TERMINA;
else if(c==':')
    al->token.tipo=TOKEN_DOSPUNTOS;
else
    {
    al->error_codigo=2;
    strcpy(al->error_mensaje,"Caracter no valido");
    return al->error_codigo;
    }
return Tlexico_push_token(al,al->sintactico);



}


int TLexico_terminarFlujo(TLexico* al)
{
	al->token.tipo=TOKEN_FALSE;
	TSintactico_PushToken(al->sintactico,&al->token);
    return 0;
}

int TLexico_getUltimoError(TLexico* al, int  * codigo, char* mensaje)
{
    return 0;
}


