#ifndef RESPONSE_GENERATOR_H
#define RESPONSE_GENERATOR_H
#include "parser.h"
#include <stddef.h>
#include <stdio.h>

enum status_code {OK=200,Not_Found=404};
//application/json, text/plain,image/jpeg,image/png
enum media_type {TEXT=1,JSON=0,JPEG=3,PNG=2};

struct Map{
	char** keys;
	char** values;
};

struct Resp{
	enum status_code code;	
	enum media_type media;
	char* content_type;	
	char* content_encoding;	
	char* content_length;	
	struct tm* Date;
	char* server;
	FILE* file;
	char* size_in_bytes;
	char* file_path;
};

void build_response(struct Req *rq,struct Resp *ret);

char* generate_resp_string(struct Resp *rp);

enum media_type get_file_extension(char *file_path);

char* get_size_of_file(FILE* file);

#endif // ! PARSER.H 

