#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(){
	//int fd[2];
	//mkfifo('tmp/fifo',S_IRWXU);
	printf("Waiting for input to be written in pipe\n");
	mkfifo("/tmp/fifo",S_IRUSR);
	int fdes = open("/tmp/fifo",O_RDONLY);
	int n;
	read(fdes,&n,4);
	close(fdes);
	fdes = open("/tmp/fifo",O_WRONLY);
	long long fact=1;
	for(int i=2;i<=n;i++) fact*=i;
	write(fdes,&fact,8);
	close(fdes);
	return 0;
}
