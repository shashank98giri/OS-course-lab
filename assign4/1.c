#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main() {
  int fdes = open("fileTask1.txt", O_RDONLY);
  char buff[100] = {};
  if (fdes == -1) {
    strcpy(buff, "File cannot be opened");
    write(1, buff, sizeof(buff));
    exit(1);
  }
  char buff2;
  while (read(fdes, &buff2, sizeof(buff2))) {
    write(1, &buff2, sizeof(buff2));
  }

  return 0;
}