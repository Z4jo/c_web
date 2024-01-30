#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include "parser.h"
#include <poll.h>

#define handleErr(msg)\
	do{perror(msg);exit(EXIT_FAILURE);} while(0)

int main(){
	char *buffer = calloc(8192,sizeof(char));
	struct sockaddr_in my_addr,peer_addr;
	socklen_t peer_addr_len = sizeof(peer_addr);
	int sock =  socket(AF_INET,SOCK_STREAM ,0);

	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(9000);


	if(bind(sock,(struct sockaddr *) &my_addr,sizeof(my_addr)) == -1){
		handleErr("build fucked up"); 
	}

	if(listen(sock,10)<0){
		handleErr("listen fucked up");
	}

		
	struct pollfd poll_s[1];
	poll_s[0].fd = sock;
	poll_s[0].events = POLLIN;
	while(1){
		int fd_number = poll((struct pollfd *) &poll_s, 1, -1);
		if (fd_number > 0){
		
			if(poll_s[0].revents == POLLIN){
				
				int client_sock = accept4(sock,(struct sockaddr*)&peer_addr,&peer_addr_len,0);
					if(client_sock == -1){
						handleErr("accept fucked up");
					}

				int recieve = recv(client_sock,buffer,8192,0);
				if(recieve==-1){
					handleErr("its fucked");
				}
				struct ArraySize lined_request;
				lined_request = read_lines(buffer);	
				printf("%s\n","we are back in this bitch");
				for(int i = 0; i< lined_request.size_in_lines; i++){
					printf("%s\n",lined_request.array[i]);
					free(lined_request.array[i]);
				}
				free(lined_request.array);
				memset(buffer, 0, 8192);

				close(client_sock); 
				strcpy(buffer, "");
			}else{
			continue;
			}
		}else{
			handleErr("poll fucked up");
		}

		}
	close(sock);
	free(buffer);

	return 0;
}




