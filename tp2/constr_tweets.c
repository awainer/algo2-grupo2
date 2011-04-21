#include "a_sintactico.h"
#include "cola.h"
#include "dict.h"
#include <stdio.h>





int Tconstructor_Crear(Tconstructor* tc); {
tc->Ecorrecto=0;
tTDiccionaro_Crear(&tc -> pd);

return NULL;
}

int Tconstructor_Destruir(Tconstructor* tc);{

return NULL;
}


int Tconstructor_setCola(Tconstructor *tc, TCola* cola){
C_Crear(&cola,&cola->TamanioDato);

return NULL;
}



int TConstructor_eventoOcurrido (Tconstructor *tc, int evento, void* dato){

return NULL;
}

