#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<time.h>
int main(){
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("10.250.1.136");
	client.sin_port=htons(8080);	
	int client_fdes=socket(AF_INET,SOCK_STREAM,0);
	int clk_st=clock();
	while(connect(client_fdes,(struct sockaddr *) &client,sizeof(client))==-1){
		if(clock()-clk_st>=10*CLOCKS_PER_SEC){

			printf("Connect not successful for client:-Time elapsed\n");
			close(client_fdes);
			exit(1);
		}
	}
	char buff[100];
	strcpy(buff,"");
	
	while(1){
		
		int valread=recv(client_fdes,buff,sizeof(buff),0);
		printf("%s",buff);
		if(valread){write(1,buff,valread);break;}
		
	}
	close(client_fdes);
	return 0;
}