#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "a_sintactico.h"
#include "a_lexico.h"
#include "parser.h"


int main(int argc, char* argv[]){
    /*char    nombrearchivo[25]=argv[1];*/
    char    nombrearchivo[25]="ejemplo.json";
	TLexico *  miLexico;
	TSintactico * miSintactico;
	TParser	* miParser;

	TLexico_Crear(miLexico);
	TSintactico_Crear(miSintactico);
	TParser_Crear(miSintactico,miLexico,nombrearchivo,miParser);



	return 0;
}
