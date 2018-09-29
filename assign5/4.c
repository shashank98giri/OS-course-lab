#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(){
	//int fd[2];
	printf("Enter no to calculate factorial:");
	int n;
	scanf("%d",&n);
	mkfifo("/tmp/fifo",S_IRUSR);
	int fdes = open("/tmp/fifo",O_WRONLY);
	write(fdes,&n,4);
	close(fdes);
	fdes = open("/tmp/fifo",O_RDONLY);
	long long ans=0;
	read(fdes,&ans,8);
	printf("Factorial of %d is :%lld\n",n,ans);
	close(fdes);
	return 0;
}
