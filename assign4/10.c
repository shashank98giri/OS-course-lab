#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
int main() {
  int fd[2];
  int x = pipe(fd);

  char buff[50];
  int r;
  srand(time(0));
  if (!fork()) {
    close(fd[0]);
    int fdes = open("Task10child1.txt", O_RDONLY, S_IRWXU);
    while (r = read(fdes, buff, 50)) {
      write(fd[1], buff, r);
      //sleep(rand() % 8 + 3);
    }
    close(fd[1]);
    close(fdes);
  } else{wait(0); if (!fork()) {
    close(fd[0]);
    int fdes = open("Task10child2.txt", O_RDONLY, S_IRWXU);
    while (r = read(fdes, buff, 50)) {
      write(fd[1], buff, r);
     // sleep(rand() % 8 + 3);
    }
    close(fd[1]);
    close(fdes);
  } else{wait(0); if (!fork()) {
    close(fd[0]);
    int fdes = open("Task10child3.txt", O_RDONLY, S_IRWXU);
    while (r = read(fdes, buff, 50)) {
      write(fd[1], buff, r);
      //sleep(rand() % 8 + 3);
    }
    close(fd[1]);
    close(fdes);

  } else {
    wait(0);
    close(fd[1]);
    //int fdes = open("Task10parent.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    int fdes=open("Task10parent.txt",O_WRONLY|O_CREAT ,S_IRWXU);
    char buff1;
    //lseek(fd[0], 0, SEEK_END);
    while (r = read(fd[0], &buff1, 1)) {
      write(fdes, &buff1, 1);
    }
    close(fdes);
    close(fd[0]);
  }
}}
  return 0;
}
