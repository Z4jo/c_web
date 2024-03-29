#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include "parser.h"
#include "response_generator.h"
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
		handleErr("build not working "); 
	}

	if(listen(sock,10)<0){
		handleErr("listen not working");
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
						handleErr("accept not working");
					}

				int recieve = recv(client_sock,buffer,8192,0);
				if(recieve==-1){
					handleErr("recv not working");
				}
				struct ArraySize lined_request;  
				lined_request = read_lines(buffer);	
				struct Req *rq = malloc(sizeof(struct Req));
				struct Resp *rp = malloc(sizeof(struct Resp));
				if (rq == NULL || rp == NULL){
					handleErr("memory not allocated");		
				}
				extract(lined_request,rq);
				build_response(rq,rp);	
				char* rp_string = generate_resp_string(rp);
				free(rq);
				free(rp);
				for(int i = 0; i< lined_request.size_in_lines; i++){
					printf("%s\n",lined_request.array[i]);
					free(lined_request.array[i]);
				}
				free(lined_request.array);
				memset(buffer, 0, 8192);
				printf("response string:%s\n",rp_string);
				send(client_sock, rp_string,strlen(rp_string),0);
				free(rp_string);
				close(client_sock); 
				strcpy(buffer, "");
			}else{
			continue;
			}
		}else{
			handleErr("poll not working");
		}

		}
	close(sock);
	free(buffer);

	return 0;
}




