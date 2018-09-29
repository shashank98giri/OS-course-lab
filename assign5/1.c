#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(){
	int fd[2];
	pipe(fd);
	if(!fork()){
		close(fd[1]);
		char buff;
		int r;
		while(read(fd[0],&buff,1)){
			write(1,&buff,1);
		}
		close(fd[0]);
	}
	close(fd[0]);
	char buff='p';
	write(fd[1],&buff,1);
	close(fd[1]);

	return 0;
}
