#include "response_generator.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
void build_response(struct Req *rq, struct Resp *ret){
	char *saveptr;
	char *path = rq->src_name;	
	char *parameter = strchr(path,'?');
	char *base_path = "./src";
	char *file_path;
	if (parameter != NULL){
		char *end= strchr(path,'\0');
		size_t path_length = parameter - path;	
		size_t parameter_length = end - parameter;	
		//TODO: parameter 
	}
	if(strcmp(path,"/")==0){
		path = "/index.html";
	}
	file_path = malloc(sizeof(strlen(path)+strlen(base_path)));
		if (file_path == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			return;
		}

	strcat(file_path,base_path);
	strcat(file_path,path);
	

	if(access(file_path,F_OK)==-1){
		//TODO:file does not exists status code change	
		ret->code = Not_Found;
	}else{
		FILE *f_resp = fopen(file_path,"rb");	
		ret->file_path = file_path;
		ret->file = f_resp;
		ret->media = get_file_extension(path);
		ret->code = OK;
		ret->size_in_bytes = get_size_of_file(f_resp);
	}
	printf("response has been build\n");	
}

char* generate_resp_string(struct Resp *rp){
	//TODO: if else code status
	char* ret;
	size_t file_size = strtoul(rp->size_in_bytes,NULL,10);
	char* file_buffer=malloc(file_size);
	char content_type_values[][20]={"application/json","text/html","image/png","image/jpeg"};
	char *crlf = "\r\n";	
	char *response = "HTTP/1.1 200 OK\r\n";
	char *header_content_type; 
	char *header_content_lenght; 
	//TODO: implement
	char *header_content_encoding = "Content-Encoding: ";
	if (rp->code == OK){
		if(rp->file == NULL){
			perror("file pointer je null");
			exit(EXIT_SUCCESS);
		}
		fseek(rp->file, 0, SEEK_SET);
		fread(file_buffer,1 , file_size, rp->file);	
		header_content_type = malloc(strlen("Content-Type: ")+strlen(content_type_values[rp->media])+strlen(crlf)); 
		header_content_lenght =  malloc(strlen("Content-Length: ")+strlen(rp->size_in_bytes)+strlen(crlf));
		if(header_content_lenght == NULL || header_content_type == NULL){
			perror("file pointer je null");
			exit(EXIT_SUCCESS);
		}
		strcat(header_content_type,"Content-Type: ");
		strcat(header_content_type,content_type_values[rp->media]);
		strcat(header_content_type,crlf);
		strcat(header_content_lenght,"Content-Length: ");
		strcat(header_content_lenght,rp->size_in_bytes);
		strcat(header_content_lenght, crlf);
		ret = malloc(strlen(response)+strlen(header_content_type)+strlen(crlf)+strlen(header_content_lenght)+file_size+1);
		if(ret==NULL){
			perror("memory was not allocated");
			exit(EXIT_FAILURE);
		}
		strcat(ret,response); 
		strcat(ret,header_content_type); 
		strcat(ret,header_content_lenght); 
		strcat(ret,crlf);
		strcat(ret,file_buffer);
	}else{
		//TODO:implement
	}
	free(file_buffer);
	free(header_content_lenght);
	free(header_content_type);
	printf("string has been generated\n");	
	return ret;
}

enum media_type get_file_extension(char *file_path){
	enum media_type ret;
	size_t lenght = strlen(file_path);
	char  *dest,*sub;
	for(int i = lenght; i>0;--i){
		if(file_path[i]=='.'){
			dest = malloc(sizeof(char)*(lenght-i));
			sub = strncpy(dest,&file_path[i],lenght-i);
			break;
		}
	}
	
	if(strncmp(sub,".txt",4)==0){
		ret = TEXT;
	}else if (strncmp(sub,".html",5)==0) {
		ret = TEXT;
	}else if (strncmp(sub,".css",5)==0) {
		ret = TEXT;
	}else if (strncmp(sub,".json",5)==0) {
		ret = JSON;
	}else if (strncmp(sub,".png",4)==0) {
		ret = PNG;
	}else if (strncmp(sub,".jpg",4)==0) {
		ret=JPEG;
	}else if (strncmp(sub,".jpeg",5)==0) {
		ret=JPEG;
	}
	return ret;
}

char* get_size_of_file(FILE *file){
	size_t size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	int max_size = snprintf(NULL, 0, "%zu",size); 
	char buffer[max_size+1];
	snprintf( buffer,sizeof(buffer), "%zu",size); 
	char *ret = buffer;
	return ret;
}


