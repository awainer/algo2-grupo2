#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#if !defined(NULL)
    #define NULL 0
#endif

#if !defined(FALSE)
    #define FALSE 0
#endif

#if !defined(TRUE)
    #define TRUE 1
#endif

typedef struct TNodoCola{
    void* Elem;
    struct TNodoCola *Siguiente;
} TNodoCola;


typedef struct{
    TNodoCola *Primero, *Ultimo;
    int TamanioDato;
} TCola;

/*
Descripci�n: Crea la cola.
Precondiciones: Cola no creada.
Postcondiciones: Cola creada y vacia.
*/
void C_Crear(TCola *pcola, int Tamanio);

/*
Descripci�n: Vac�a la Cola.
Precondiciones: Cola creada.
Postcondiciones: Cola vac�a.
*/
void C_Vaciar(Tcola *pcola);

/*
Descripci�n: Avisa si la cola esta vac�a.
Precondiciones: Cola creada.
Postcondiciones: Si la cola esta vac�a devuelve TRUE, sino FALSE
*/
int C_Vacia(Tcola c);

/*
Descripci�n: Agrega elemento a la cola y devuelve TRUE, si no se pudo agregar devuelve FALSE.
Precondiciones: Cola creada.
Postcondiciones: Elemento agregado como �ltimo elemento de la cola. Devuelve FALSE si no pudo agregarlo, sino TRUE.
*/
int C_Agregar(TCola *pcola, void *pElem);

/*
Descripci�n: Extrae elemento de la cola.
Precondiciones: cola creada y no vacia.
Postcondiciones: Se extrajo el primer elemento de la cola. Si no se pudo extraer devuelve FALSE, sino TRUE.
*/
int C_Sacar(TCola *pcola, void *pElem);


#endif // COLA_H_INCLUDED
