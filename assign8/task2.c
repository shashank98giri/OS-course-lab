#include<unistd.h>
#include<bits/pthreadtypes.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
sem_t full,empty,mutex;
int in=0,out=0;
void consumer(){
    while(1){
    sem_wait(&full); 
    sem_wait(&mutex);
    
    int next_consumed=buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    sem_post(&mutex);
    sem_post(&empty);
    
    printf("Value Read %d\n",ext_consumed);
    }
} 
void producer() 
{ 
    int next_produced=0;
    while(1){    
    next_produced++;
    sem_wait(&empty); 
    sem_wait(&mutex);

    // critical section: Put item into shared buffer
    buffer[in]=next_produced;
    in = (in + 1) % BUFFER_SIZE;
    sem_post(&mutex);
    sem_post(&full);
    }
} 
  
  
int main() 
{ 
    int n=10;
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0); 
    sem_init(&empty, 0, n);    
    pthread_t t1,t2; 
    pthread_create(&t1,NULL,(void*)consumer,NULL); 
    pthread_create(&t2,NULL,(void*)producer,NULL); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    sem_destroy(&mutex);
    sem_destroy(&full); 
    sem_destroy(&empty); 
 
    return 0; 
} 