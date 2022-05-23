#include "hello_world.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILENAME "/text.txt"

void fatal(char *message) {
  char *prefix = "[!!] Fatal error: ";
  strncat(prefix, message, strlen(message));
  perror(prefix);
  exit(-1);
}

void open_file_and_print() {
  int fd;
  char *buffer;
  fd = open(FILENAME, O_RDONLY);
  if (fd == -1)
    fatal("Couldn't open file");

  read(fd, buffer, 1000);
  if (fd == -1)
    fatal("Couldn't read file");

  close(fd);

  printf("%s\n", buffer);
}

int main() {
  printf("Custom initramfs - Hello World syscall:\n");
  hello_world();
  open_file_and_print();

  printf("Finished kernel init!\n");
  for (;;)
    sleep(1000);

  return 0;
}
