#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<bits/pthreadtypes.h>
#include<pthread.h>
int s=10;
void func1(){
	s*=10;
	printf("value from thread 1: %d\n",s);

}
void func2(){
	s+=10;
	printf("value from thread 2: %d\n",s);
	
}
void func3(){
	s/=10;
	printf("value from thread 3: %d\n",s);
	
}
void func4(){
	s/=10;
	printf("value from thread 4: %d\n",s);
	
}
int main(){
	pthread_t tid[4];
	
	pthread_create(&tid[0],NULL,(void *)func1,NULL);
	pthread_create(&tid[1],NULL,(void *)func2,NULL);
	pthread_create(&tid[2],NULL,(void *)func3,NULL);
	pthread_create(&tid[3],NULL,(void *)func4,NULL);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);
	printf("final value: %d\n",s);
	return 0;
}