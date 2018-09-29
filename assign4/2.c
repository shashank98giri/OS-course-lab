#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main() {
  int fdes = open("fileTask1.txt", O_RDONLY);
  char buff[100];
  if (fdes == -1) {
    strcpy(buff, "File cannot be opened");
    write(1, buff, sizeof(buff));
    exit(1);
  }
  
  while (1) {
    memset(buff,'\0',sizeof(buff));
    int byt=read(fdes, buff, sizeof(buff));
    if(byt==-1||!byt)exit(0);
    write(1, buff, sizeof(buff));
  }

  return 0;
}
