#include "a_sintactico.h"
#include "cola.h"
#include "dict.h"






int Tconstructor_Crear(Tconstructor* tc); {

C_Crear(&tc->pcola,2*sizeof(int*));
tc->Ecorrecto=0;
tTDiccionaro_Crear(&tc);
return 0;
}

int Tconstructor_Destruir(TConstructor* tc);{


}


int Tconstructor_setCola(TConstructor *tc, TCola* cola);



int TConstructor_eventoOcurrido (TConstructor *tc, int evento, void* dato);

