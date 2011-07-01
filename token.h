#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED



#define MAX_DATO 4096

typedef enum{
    TOKEN_STRING,
    TOKEN_NUMERO,
    TOKEN_OBJETO_EMPIEZA,
    TOKEN_OBJETO_TERMINA,
    TOKEN_ARRAY_EMPIEZA,
    TOKEN_ARRAY_TERMINA,
    TOKEN_COMA,
    TOKEN_DOSPUNTOS,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL
}TipoToken;

typedef struct token{
    int tipo;
    char dato[MAX_DATO];
}Token;
#endif
