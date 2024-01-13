#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include "parser.h"

#define handleErr(msg)\
	do{perror(msg);exit(EXIT_FAILURE);} while(0)

int main(){
	char *buffer = calloc(8192,sizeof(char));
	struct sockaddr_in my_addr,peer_addr;
	socklen_t peer_addr_len = sizeof(peer_addr);
	int sock =  socket(AF_INET,SOCK_STREAM,0);

	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(9000);

	if(bind(sock,(struct sockaddr *) &my_addr,sizeof(my_addr)) == -1){
		handleErr("build fucked up"); 
	}

	if(listen(sock,10)<0){
		handleErr("listen fucked up");
	}

	int client_sock = accept(sock,(struct sockaddr*)&peer_addr,&peer_addr_len);
		if(client_sock == -1){
			handleErr("accept fucked up");
		}

	while(1){

		int recieve = recv(client_sock,buffer,8192,0);
		if(recieve==-1){
			handleErr("its fucked");
		}
		//printf("%s\n",buffer);
		char **ret = read_lines(buffer);	
		continue;
	}
		
	close(client_sock); 
	close(sock);
	return 0;
}




