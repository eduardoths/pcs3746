#include "hello_world.h"
#include <stdio.h>

int main() {
  printf("Custom initramfs - Hello World syscall:\n");
  hello_world();

  printf("Finished kernel init!\n");
  for (;;)
    sleep(1000);

  return 0;
}
