#ifndef PARSER_H
#define PARSER_H

enum request_type {GET=1,POST=2,ERR=3};

struct Req{
	char* src_name;	
	enum request_type req;
};

struct ArraySize{
	char** array;
	int size_in_lines;
};

struct ArraySize read_lines(char *buffer);

void extract(struct ArraySize arr, struct Req *ret);

#endif // ! PARSER.H 

