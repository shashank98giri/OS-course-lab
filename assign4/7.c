#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main() {
  //close(0), close(1);
  int fdes = open("fileTask6stdin.txt", O_RDONLY);
  int fdes1 = open("fileTask7stdout.txt", O_WRONLY | O_CREAT, S_IRWXU );
  close(0);
  dup(fdes);close(1);dup(fdes1);
  char temp;
  while(read(0, &temp, 1)) {
    write(1, &temp, 1);
  }

  return 0;
}
