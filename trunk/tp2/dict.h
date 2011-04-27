#ifndef DICT_H_
#define DICT_H_
#include "lista.h"

typedef struct {
    char *k,*v;
}Definicion;

typedef struct {
    TListaSimple elementos;
}TDiccionario;

/*pre: Ninguna
post: El diccionario ha sido creado*/
int TDiccionaro_Crear(TDiccionario* td);

/*pre: El diccionario ha sido creado
post: Se liberaron los recursos asociados al diccionario*/
int Tdiccionario_Destruir(TDiccionario* td);

/*pre: El diccionario ha sido creado
post: Se coloca en el diccionario el equivalente a diccionario[clave] = valor. Si clave ya existia en el
diccionario, su valor se reemplaza por el nuevo. Se coloca una copia del texto (no un puntero).*/
int TDiccionario_colocar(TDiccionario* td, char* clave, char* valor);

/*pre: El diccionario ha sido creado. Existe la entrada “clave” en el diccionario. Buffer tiene el
tamaño suficiente para guardar el texto
post: se guarda en buffer una copia del texto en el diccionario bajo la clave. Es el equivalente a
buffer = diccionario[clave]*/
int TDiccionario_obtener(TDiccionario* td, char* clave, char* buffer);

/*pre: el diccionario ha sido creado
post: devuelve el tamaño del texto asociado con la clave a fin de poder reservar un buffer donde
quepa el texto y obtenerlo con Tdiccionario_obtener. Si la clave no esta en el diccionario devuelve
0.
*/
int TDiccionario_sizeDato(TDiccionario* td, char* clave);


int compstr(const void *s1, const void *s2);



#endif /* DICT_H_ */
