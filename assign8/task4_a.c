#include<unistd.h>
#include<bits/pthreadtypes.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

sem_t a,b;
int cnt=0;
void T_1(){
	while(cnt++<10){	
	sem_wait(&a);
	printf("A");
	sem_post(&b);
	//sem_post(&turn);
	//sleep(1);
	}
}
void T_2(){
	while(cnt++<10){
	sem_wait(&b);
	//sem_wait(&sem);
	printf("B");
	sem_post(&a);
	//sem_post(&turn);
	//sleep(1);
	}
}
int main(){
	sem_init(&a,0,1);sem_init(&b,0,0);
	pthread_t tid[2];
	pthread_create(&tid[0],NULL,(void *)T_1,NULL);
	pthread_create(&tid[1],NULL,(void *)T_2,NULL);
	//pthread_create(&c,NULL,(void *)take_exam,NULL);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	sem_destroy(a);sem_destroy(b);
	//pthread_join(c,NULL);
	return 0;
}