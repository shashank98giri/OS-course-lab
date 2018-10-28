#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<bits/pthreadtypes.h>
#include<pthread.h>
#include<semaphore.h>
int s=10;
sem_t sem;
void func1(){
	sem_wait(&sem);
	s*=10;
	printf("value from thread 1: %d\n",s);
	sem_post(&sem);

}
void func2(){
	sem_wait(&sem);
	s+=10;
	printf("value from thread 2: %d\n",s);
	sem_post(&sem);
}

int main(){
	pthread_t tid[2];

	sem_init(&sem,0,1);
	pthread_create(&tid[0],NULL,(void *)func1,NULL);
	pthread_create(&tid[1],NULL,(void *)func2,NULL);
	
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	sem_destroy(&sem);
	printf("final value: %d\n",s);
	return 0;
}