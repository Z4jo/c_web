#ifndef PARSER_H
#define PARSER_H

struct ArraySize{
	char** array;
	int size_in_lines;
};

struct ArraySize read_lines(char *buffer);

#endif // ! PARSER.H 

