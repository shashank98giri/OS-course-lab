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
// pushing data

sem_t sem;//shared semaphore variable

void push(data* info,char val){
	if(info->st == -1){
		info->st = 0;
		info->en = 0;
	}
	info->buff[info->en] = val;
	info->en = (info->en+1)%BUFFER_SIZE;
}
//checking for full
int is_full(data *info){
	return (info->st!=-1&&info->st==info->en);
}
int main(){
	
	key_t key=ftok("1.c",53);
	int segid=shmget(key,sizeof(data),0777|IPC_CREAT);
	int sema_id=shmget(key1,sizeof(sem),0777|IPC_CREAT);
	data *info=(data*)shmat(segid,NULL,SHM_RND);
	info->st=-1;info->en=-1;
	for(int i=0;i<100;i++){
		while(is_full(info));
		char val='A'+rand()%26;
		printf("%c",val);
		push(info,val);
		fflush(stdout);
	}

	shmdt(info);
	return 0;
}
