#ifndef DICT_H_
#define DICT_H_

typedef struct {
	char *	k,v;
}TPar;

typedef struct {
	TPar * elementos[];
	int	 e_count;
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
Int TDiccionario_colocar(TDiccionario* td, char* clave, char* valor);

/*pre: El diccionario ha sido creado. Existe la entrada “clave” en el diccionario. Buffer tiene el
tamaño suficiente para guardar el texto
post: se guarda en buffer una copia del texto en el diccionario bajo la clave. Es el equivalente a
buffer = diccionario[clave]*/
int TDiccionario_obtener(TDiccionario* td, char* clave, char* buffer);

int TDiccionario_sizeDato(TDiccionario* td, char* clave);

#endif /* DICT_H_ */