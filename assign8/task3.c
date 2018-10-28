#include<unistd.h>
#include<bits/pthreadtypes.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

sem_t sem;
void drink_coffee(){
	//sem_wait(&sem);
	printf("Drink coffee from thread B\n");
	sem_post(&sem);
}
void study_os(){
	//sem_wait(&sem);
	printf("Study os from thread A\n");
	sem_post(&sem);
}
void take_exam(){
	sem_wait(&sem);
	printf("Take exam from thread C\n");
	sem_post(&sem);
}
int main(){
	sem_init(&sem,0,-1);
	pthread_t a,b,c;
	pthread_create(&a,NULL,(void *)drink_coffee,NULL);
	pthread_create(&b,NULL,(void *)study_os,NULL);
	pthread_create(&c,NULL,(void *)take_exam,NULL);
	pthread_join(a,NULL);
	pthread_join(b,NULL);
	pthread_join(c,NULL);
	sem_destroy(&sem);
	return 0;
}