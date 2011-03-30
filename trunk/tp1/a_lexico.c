/*Implementaciones del TDA TLexico*/

#include "a_lexico.h"
#include <string.h>


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
        al->buffer_idx++;
        }
        else
        {
            /* Si recibo una comilla con el indice distinto de -1,
            tengo que terminar el string y resetear */
            al->buffer_idx=-1;
            al->token.tipo=TOKEN_NULL;
            if (TSintactico_PushToken(al->sintactico,&al->token))
            {
                return 0;
            }
            else
            {
                al->error_codigo=1;
                strcpy(al->error_mensaje,"El asintactico me devolvio error");
            }
        }

    }
    /*Recibo letras */
    else if ( (( c >= 'a' )&&( c <= 'z' ) ) || ( (c>='A') && (c<='Z') ))
    {
    	if ((al->buffer_idx!=-1) && (al->token.tipo!=TOKEN_STRING))
    	{
    		/*Si el indice del buffer no esta en -1 (hay data previa) y no estamos guardando un string
    		 * entonces probablemente hayamos recibido una letra en medio de un numero*/
    		al->error_codigo=1;
    		strcpy(al->error_mensaje,"Recibi una letra pero no estaba dentro de un string");
    		return al->error_codigo;
    	}
    	al->token.tipo=TOKEN_STRING;
        al->token.dato[al->buffer_idx]=c;
        al->token.dato[al->buffer_idx+1]='\0';
        al->buffer_idx++;
    }
    /*Recibo numeros*/
    else if((c>='0') && (c<='9'))
    {
      	if ((al->buffer_idx!=-1) && (al->token.tipo!=TOKEN_NUMERO))
        	{
        		/*Si el indice del buffer no esta en -1 (hay data previa) y no estamos guardando un numero
        		 * entonces probablemente hayamos recibido una numero en medio de un string o cualquier otra cosa*/
        		al->error_codigo=1;
        		strcpy(al->error_mensaje,"Recibi una numero pero no estaba dentro de una variable numerica");
        		return al->error_codigo;
        	}

      al->buffer_idx++;
      al->token.tipo=TOKEN_NUMERO;
      al->token.dato[al->buffer_idx]=c;

    }
    /*Recibo comas*/
    else if(c==',')
    {
        if(al->token.tipo==TOKEN_NUMERO)
        {
            /*Si recibo una coma cuando estaba recibiendo un numero, termina
            En ese caso, tengo que mandar el token del numero y el de la coma*/
            if (TSintactico_PushToken(al->sintactico,&al->token))
            {
                al->token.tipo=TOKEN_COMA;
                if (TSintactico_PushToken(al->sintactico,&al->token))
                {
                    /* Esto lo hago como ifs anidados porque si lo pongo como
                    un solo if de dos condiciones no se cual va a ejecutar primero*/
                al->buffer_idx=-1;
                al->token.tipo=TOKEN_NULL;
                return 0;
                }
            }
            else
            {
                al->error_codigo=1;
                strcpy(al->error_mensaje,"El asintactico me devolvio error");
            }
        }

        else
        if (al->buffer_idx==-1)
        {


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
            else if( (c=='\n') || (c==' ') )
                al->token.tipo=TOKEN_FALSE;
            else
            {
                al->error_codigo=2;
                strcpy(al->error_mensaje,"Caracter no valido");
                return al->error_codigo;
            }
        }
        else
        {
            /* Recibi un token 'atomico' cuando el indice no era -1, es un eror lexico*/
                al->error_codigo=2;
                strcpy(al->error_mensaje,"No estaba esperando este caracter");
                return al->error_codigo;
        }


        /* Ahora mandamos tokens atomicos*/
        if (TSintactico_PushToken(al->sintactico,&al->token))
        {
        	/* Reseteo el token */
            al->buffer_idx=-1;
            al->token.tipo=TOKEN_NULL;
            return 0;
        }
        else
         {
           al->error_codigo=1;
           strcpy(al->error_mensaje,"El asintactico me devolvio error");
         }

    }


 /*fin de PushChar no deberia llegar nunca aca, deberia retornar antes*/
return 4;

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


