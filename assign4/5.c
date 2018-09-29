#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main() {

  
  int fdes=open("fileTask1.txt",O_RDONLY);
  char buff[100];
  if (fdes == -1) {
    strcpy(buff, "File cannot be opened");
    write(1, buff, sizeof(buff));
    exit(1);
  }
  int cnt=0;char buff1;
  int offset=lseek(fdes,0,SEEK_END);
  while (offset) {
    //memset(buff,'\0',sizeof(buff));
    lseek(fdes,-2,SEEK_CUR);
    int byt=read(fdes, &buff1, sizeof(buff1));
    write(1, &buff1, sizeof(buff1));
    offset--;
  }

  return 0;
}
