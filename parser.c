#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

char ** read_lines(char *buffer){
	char ** ret = NULL;
	char *saveptr1, *line;
	int number_of_lines = 0;
	for(int i = 0; buffer[i]!='\0';++i){
		line = strtok_r(buffer,"\n",&saveptr1);   
		while(line != NULL){
			if(*line == '\n'){
				break;
			}
			ret = (char **) realloc(ret, (number_of_lines+1) * sizeof(char * ));
			ret[number_of_lines] = malloc(strlen(line)+1);
			printf("%s\n",line);
			strcpy(ret[number_of_lines],line);
			number_of_lines++;
			line = strtok_r(NULL,"\n",&saveptr1);		
		}
	}	

	for (int i = 0 ;number_of_lines;++i){
		printf("%s\n",ret[i]);
		printf("%d\n",i);
	}
	return ret;
}	
