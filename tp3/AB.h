#ifndef __ARBOLBINARIO_H__
	#define __ARBOLBINARIO_H__
	
	#include <stdlib.h>
	#include <memory.h>
	
	#define IZQ 1
	#define DER 2
	#define PAD 3
	#define RAIZ 4

	#if !defined(RES_OK)
		#define RES_OK 0
	#endif

	#if !defined(RES_MOV_INVALIDO)
		#define RES_MOV_INVALIDO -1
	#endif

	#if !defined(RES_ARBOL_VACIO)
		#define RES_ARBOL_VACIO -4
	#endif
	
	#if !defined(NULL)
		#define NULL 0x0
	#endif
	
	#if !defined(FALSE)
		#define FALSE 0
	#endif
	
	#if !defined(TRUE)
		#define TRUE 1
	#endif
	
	typedef struct TNodoAB
	{
		void* elem;
		struct TNodoAB *izq, *der;
	} TNodoAB;
	
	typedef struct TAB
	{
		TNodoAB *raiz,*cte;
		int tamdato;
	} TAB;
	
	void AB_Crear(TAB *a,int tdato);
	
	void AB_ElemCte(TAB a,void *elem);
	
	void AB_ModifCte(TAB *a,void *elem);
	
	int AB_MoverCte(TAB *a,int mov);
	
	void AB_Vaciar(TAB *a);
	
	int AB_Vacio(TAB a);
	
	int AB_Insertar(TAB *a,int mov,void *elem);
	
	int AB_BorrarRama(TAB *a);

	int AB_BorrarSubRama(TAB *a, int mov);

#endif

