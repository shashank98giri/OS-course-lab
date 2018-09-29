#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<pthread.h>
#include<bits/pthreadtypes.h>
int val;
int func(void* n){
	int num=*((int*)n);
	int cnt=0;
	for(int i=1;i<=num;i++)if(num%i==0)cnt++;
	val=(cnt==2);
}
int main(){
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("10.250.1.136");
	server.sin_port=htons(8080);	
	int server_fdes=socket(AF_INET,SOCK_STREAM,0);
	if(bind(server_fdes,(struct sockaddr *) &server,sizeof(server))==-1){
		printf("Bind not successful for server\n");
		exit(1);
	}
	int c=sizeof(struct sockaddr_in);
	int client_fdes;
	listen(server_fdes,3);
	if((client_fdes = accept(server_fdes, (struct sockaddr *)&client,(socklen_t*)&c))==-1){
			printf("Error in client connection accpeting\n");
			exit(1);
	}			
	
	while(1){
		
		char buff[100];strcpy(buff,"");
		int num;pthread_t tid;
		read(client_fdes,&num,sizeof(num));
		pthread_create(&tid,NULL,(void *)func,&num);
		pthread_join(tid,NULL);
		
		if(val)strcpy(buff,"YES\n");
		else strcpy(buff,"NO\n");
		write(client_fdes,buff,sizeof(buff));
		
		
	}
	close(client_fdes);	
	close(server_fdes);
	return 0;
}