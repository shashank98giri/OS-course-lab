#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
int main(){
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("10.250.1.136");
	client.sin_port=htons(8080);	
	int client_fdes=socket(AF_INET,SOCK_STREAM,0);
	
	if(connect(client_fdes,(struct sockaddr *) &client,sizeof(client))==-1){
		printf("Connect not successful for client\n");
		exit(1);
	}
	char buff[100];
	int valread=recv(client_fdes,buff,sizeof(buff),0);
	write(1,buff,valread);
	close(client_fdes);
	return 0;
}