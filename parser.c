#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

struct ArraySize read_lines(char *buffer){
	char ** lines= NULL;
	char *saveptr1, *line;
	printf("%s\n","read_lines:ON");
	int number_of_lines = 0;
	line = strtok_r(buffer,"\n",&saveptr1);   
	while(line != NULL){
		if(isspace(*line)){ 
			break;
		}
		lines= (char **) realloc(lines, (number_of_lines+1) * sizeof(char * ));
		lines[number_of_lines] = malloc(strlen(line)+1);
		strcpy(lines[number_of_lines],line);
		number_of_lines++;
		line = strtok_r(NULL,"\n",&saveptr1);		
	}
	
	struct ArraySize ret;
	ret.array=lines;
	ret.size_in_lines=number_of_lines;
	return ret;
}	

void extract(struct ArraySize arr, struct Req *ret){
	for(int i = 0; i<arr.size_in_lines; ++i){
		if(i == 0){
			char *saveptr, *word;
			word = strtok_r(arr.array[i]," ",&saveptr);   
			for(int j = 0; word != NULL; ++j){
				if(j == 0 ){
					if(strcmp(word,"GET")){
						ret->req = GET;			
					} else if (strcmp(word,"POST")){
						ret->req = POST;
					}else{
						ret->req = ERR;
					}

				}else if(j == 1){
					ret->src_name = word;	
				}
				word = strtok_r(NULL," ",&saveptr);
			}
		}
	}

	printf("we are done extracting\n");
}
