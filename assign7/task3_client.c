#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<pthread.h>
#include<bits/pthreadtypes.h>
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
	while(1){
		char buff[100];strcpy(buff,"");
		int num;
		scanf("%d",&num);
		write(client_fdes,&num,sizeof(num));
		int valread=recv(client_fdes,buff,strlen(buff),0);
		write(1,buff,valread);
		fflush(stdout);		
	}
	close(client_fdes);
	return 0;
}