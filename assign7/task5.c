#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<bits/pthreadtypes.h>
#include<pthread.h>
int fib[100010];
void fibonacci(void *num){
	fib[0]=0;fib[1]=1;
	int n=*((int*)num);
	for(int i=2;i<=n;i++)
		fib[i]=fib[i-1]+fib[i-2];
	
}


int main(){
	pthread_t tid;
	int num;scanf("%d",&num);
	pthread_create(&tid,NULL,(void *)fibonacci,(void *)&num);
	pthread_join(tid,NULL);
	for(int i=0;i<=num;i++)printf("%d ",fib[i]);	

	return 0;
}