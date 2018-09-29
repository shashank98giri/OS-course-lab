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
	int number;
	scanf("%d",&number);
	write(client_fdes,&number,sizeof(number));
	int ans;
	recv(client_fdes,&ans,sizeof(ans),0);
	printf("%d",ans);
	//write(1,&ans,sizeof(ans));
	return 0;
}