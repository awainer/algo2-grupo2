
#ifndef PARSER_H_
#define PARSER_H_


typedef struct t_parser{
	TSintactico as;
	TLexico lex;
	FILE*	arch;
}TParser;

int TParser_crear(TSintactico*  ts,TLexico * tl,FILE * arch,TParser * parser);
int TParser_parsear(TParser * parser);

#endif

