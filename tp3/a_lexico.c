
/*Implementaciones del TDA TLexico*/

#include "a_lexico.h"
#include "a_sintactico.h"
#include <string.h>
#include <stdio.h>
#include "parser.h"

int TLexico_Crear(TLexico* al)
{
    al->error_codigo=0;
    al->buffer_idx=-1;
    al->token.tipo=TOKEN_NULL;
    al->token.dato[0]=0;
    strcpy(al->palabras_reservadas[0],"null");
    strcpy(al->palabras_reservadas[1],"true");
    strcpy(al->palabras_reservadas[2],"false");
    /* indice para saber que palabra reservada estamos acumulando*/
    al->palabra_idx=-1;
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
                al->palabra_idx=-1;
                al->token.dato[0]=0;
                return 0;
            }

            else
            {
                al->error_codigo=E_SINTACTICO;
                strcpy(al->error_mensaje,"El asintactico me devolvio error");
                /*printf("Error sintactico");*/
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
    if((c==' ' ) || (c=='\t') || (c=='\n')) /*Un espacio o tab termina un numero */
    {
    return Tlexico_push_token(al,al->sintactico);
    }
    /*Todos estos son otros caracteres que delimitan un numero, para los que tengo que enviar dos tokens, esto habria que modularizarlo un poco */
    if(c==',')
    {
        if(Tlexico_push_token(al,al->sintactico)==0)
        {
         al->token.tipo=TOKEN_COMA;
         return Tlexico_push_token(al,al->sintactico);
        }
        else
        {
            al->error_codigo=E_SINTACTICO;
            strcpy(al->error_mensaje,"El asintactico me devolvio error");
            /*printf("Error sintactico");*/
            return al->error_codigo;
        }
    }
    else if(c==']')
    {
        if(Tlexico_push_token(al,al->sintactico)==0)
        {
         al->token.tipo=TOKEN_ARRAY_TERMINA;
         return Tlexico_push_token(al,al->sintactico);
        }
        else
        {
            al->error_codigo=E_SINTACTICO;
            strcpy(al->error_mensaje,"El asintactico me devolvio error");
            /*printf("Error sintactico");*/
            return al->error_codigo;
        }
    }
    else if(c=='}')

    {
        if(Tlexico_push_token(al,al->sintactico)==0)
        {
         al->token.tipo=TOKEN_OBJETO_TERMINA;
         return Tlexico_push_token(al,al->sintactico);
        }
        else
        {
            al->error_codigo=E_SINTACTICO;
            strcpy(al->error_mensaje,"El asintactico me devolvio error");
            /*printf("Error sintactico");*/
            return al->error_codigo;
        }
    }

    else{

        al->error_codigo=E_LEXICO;
        strcpy(al->error_mensaje,"Caracter inesperado en medio de un numero");
        /*printf("Error lexico");*/
        return al->error_codigo;
    }
}

/*Estamos juntando un string */
if (al->token.tipo==TOKEN_STRING)
{
    /*if ( (( c >= 'a' )&&( c <= 'z' ) ) || ( (c>='A') && (c<='Z') ) || (c==' ') || (c =='\t') || ( (c>='0') && (c<='9')  )   )*/
    if( ( c!='"') && (c!=0))

    {
        tlexico_acumular_dato(al,c);
        return 0;
    }
    else
    {
      		al->error_codigo=E_LEXICO;
       		strcpy(al->error_mensaje,"Recibi un caracter no valido dentro de un string");
       		return al->error_codigo;
    }
}

/*comienzos de palabras reservadas
Afortunadamente no existen dos palabras reservadas con la misma inicial*/
if(c=='n')
{
    al->token.tipo=TOKEN_NULL;
    tlexico_acumular_dato(al,c);
    al->palabra_idx=0;
    return 0;
}

if(c=='t')
{
    al->token.tipo=TOKEN_TRUE;
    tlexico_acumular_dato(al,c);
    al->palabra_idx=1;
    return 0;
}

if(c=='f')
{
    al->token.tipo=TOKEN_FALSE;
    tlexico_acumular_dato(al,c);
    al->palabra_idx=2;
    return 0;
}

/* ahora estamos juntando una palabra reservada*/
if(al->palabra_idx!=-1)
{   /*La primera condicion chequea que el caracter coincida con el string de
    la palabra reservada que continua
    La segunda condicion chequea que no se exceda en cantidad de caracteres*/
    if((c==al->palabras_reservadas[al->palabra_idx][al->buffer_idx+1]) &&
       (al->buffer_idx < strlen( al->palabras_reservadas[al->palabra_idx] )))
       {
       tlexico_acumular_dato(al,c);
       /* nos fijamos si termino la palabra */
       if(strcmp(al->token.dato,al->palabras_reservadas[al->palabra_idx])==0)
       {
        /*entonces termine de acumular una palabra reservada*/
            if(Tlexico_push_token(al,al->sintactico)==0)
                return 0;
            else
            {
                al->error_codigo=E_SINTACTICO;
                strcpy(al->error_mensaje,"El asintactico me devolvio error");
                /*printf("Error sintactico");*/
                return al->error_codigo;
            }

        }

        return 0;

       }

    else
       {/* printf("%d",strlen(al->token.dato));*/
        al->error_codigo=E_LEXICO;
        strcpy(al->error_mensaje,"Caracter no valido en medio de palabra reservada");
        /*printf("error lexico\n");*/
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
else if(c==',')
    al->token.tipo=TOKEN_COMA;
else if ((c==' ') || (c=='\t') || (c=='\n') || (c==10) || (c==13))
        /* 10=CL, 13=CF*/
        /* Estos caracteres no tienen significado a nivel sintactico, asi que no paso nada*/
        return 0;

else
    {
    al->error_codigo=E_LEXICO;
    strcpy(al->error_mensaje,"Caracter no valido");
    /*printf("error lexico\n");*/
    return al->error_codigo;
    }
return Tlexico_push_token(al,al->sintactico);



}


int TLexico_terminarFlujo(TLexico* al)
{
if(al->error_codigo==0)
{


    if(al->buffer_idx==-1)
    {
       /*En este caso, se termina el flujo ok a nivel lexico, vemos que pasa a nivel sintactico */
       if(TSintactico_terminarFlujo(al->sintactico)==1)
       {
           return E_SINTACTICO;
       }
    }
    else
    {
        strcpy(al->error_mensaje,"Fin de flujo antes de terminar el token");
        al->error_codigo=E_LEXICO;
        return al->error_codigo;
    }

    return 0;
}
/* Si ya habia ocurrido un error, no quiero modificarlo.*/
return al->error_codigo;
}

int TLexico_getUltimoError(TLexico* al, int  * codigo, char* mensaje)
{
    *codigo=al->error_codigo;
    strcpy(mensaje,al->error_mensaje);
    return 0;
}


