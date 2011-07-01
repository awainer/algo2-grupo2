#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#include "lista.h"

typedef struct ListaOrdenada{
    TListaSimple elementos;
    int (*cmp)(void*,void*);
    int tamanioDato;
}TListaOrdenada;

void LO_Crear(TListaOrdenada *pLs, int TamanioDato,int (*cmp)(void*,void*));

/**
* L_VACIAR
* Pre: Ls creada.
* Post: Ls vacia.
*/
void LO_Vaciar(TListaOrdenada *pLs);

	/**
	 * L_VACIA
	 * Pre: Ls creada.
	 * Post: Si Ls tiene elementos devuelve FALSE sino TRUE.
	 */
int LO_Vacia(TListaOrdenada Ls);

	/**
	 * L_ELEM_CTE
	 * Pre: Ls creada y no vacia.
	 * Post: Se devuelve en E el elemento Corriente de la lista.
	 */
void LO_Elem_Cte(TListaOrdenada Ls, void* pE);

	/**
	 * L_MOVER_CTE
	 * Pre: Ls creada y no vacia.
	 * Post: Si Ls esta vacia, devuelve FALSE. Sino:
	 * Si M = L_Primero, el nuevo elemento Corriente es el Primero. Devuelve TRUE
	 * Si M = L_Siguiente, el nuevo elemento Corriente es el Siguiente al
	 * Anterior. Si estaba en el ultimo elemento, devuelve FALSE, sino TRUE.
	 * Si M = L_Anterior, devuelve FALSE.
	 */
	int LO_Mover_Cte(TListaOrdenada *pLs, TMovimiento_Ls M);

	/**
	 * L_BORRAR_CTE
	 * Pre: Ls creada y no vacia.
	 * Post: Se elimino el elemento Corriente, El nuevo elemento es el Siguiente o
	 * el Anterior si el Corriente era el ultimo elemento.
	 */
	void LO_Borrar_Cte(TListaOrdenada *pLs);

	/**
	 * L_INSERTAR_CTE
	 * Pre: Ls creada.
	 * Post: E se agrego a la lista y es el actual elemento Corriente.
	 * Si M=L_Primero: se inserto como Primero de la lista.
	 * Si M=L_Siguiente: se inserto despues del elemento Corriente.
	 * Si M=L_Anterior: se inserto antes del elemento Corriente.
	 * Si pudo insertar el elemento devuelve TRUE, sino FALSE.
	 */
	int LO_Insertar(TListaOrdenada *pLs, void* E);

    void LO_Destruir(TListaOrdenada * pLs);

#endif
