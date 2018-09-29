#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main() {
  close(0), close(1);
  int file = open("fileTask6stdin.txt", O_RDONLY);
  int file_output = open("fileTask6stdout.txt", O_WRONLY | O_CREAT, S_IRWXU );
  char temp;
  while(read(0, &temp, 1)) {
    write(1, &temp, 1);
  }

  return 0
}
