#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Pila.h"
#include "token.h"
#include "constr_tweets.h"

#ifndef _VAR_ARRAY_H_
#define _VAR_ARRAY_H_

typedef struct Var_Array{
    void* array;
    int a_size, a_count, e_size;
}V_Array;

typedef int (*funccmp)(void*, void*);

int VA_create(V_Array* a, int elemsize);
int VA_count(V_Array a);
int VA_add(V_Array* a, void* elem);
int VA_get_i(V_Array a, int epos, void* elem);
void* VA_get(V_Array* a);
int VA_set(V_Array* a, int epos, void* elem);
int VA_remove(V_Array* a, int epos);
void VA_destroy(V_Array* a);

int VA_sort(V_Array* a, funccmp cmp);
void VA_qsort(V_Array* a, funccmp cmp, int inicio, int fin);

/** Primitiva agregada **/
/*Descipción: Imprime el vector ya ordenado y cuenta la cantidad de datos repetidos y los imprime en la misma linea, en este caso, cantidad de tweets
Precondiciones: Existe array dinamico y esta ORDENADO.
Postcondiciones: Imprime el dato y la cantidad de veces que se repite el dato.
*/
void VA_print_ordered(V_Array a);

#endif
