#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "a_sintactico.h"
#include "a_lexico.h"
#include "parser.h"


int main(int argc, char* argv[]){
	FILE * archivo;
	TLexico *  miLexico;
	TSintactico * miSintactico;
	TParser	* miParser;

	TLexico_Crear(miLexico);
	TSintactico_Crear(miSintactico);




	return 0;
}
