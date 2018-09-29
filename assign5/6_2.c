#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#define BUFFER_SIZE 10
typedef struct{
	char buff[BUFFER_SIZE];
	int st,en;
} data;
//  popping element
char pop(data* info){
	char val=info->buff[info->st];
	info->st=(info->st+1)%BUFFER_SIZE;
	if(info->st==info->en){
		info->st=-1;info->en=-1;
	}
	return val;
}
//checking for empty
int is_empty(data *info){
	return info->st==-1;
}
int main(){
	
	key_t key=ftok("1.c",53);
	int segid=shmget(key,sizeof(data),0777|IPC_CREAT);
	data *info=(data*)shmat(segid,NULL,SHM_RND);
	for(int i=0;i<100;i++){
		while(is_empty(info));
		char val=pop(info);
		printf("%c",val);
		fflush(stdout);
		//pop(info,val);
	}
	
	shmdt(info);
	return 0;
}
