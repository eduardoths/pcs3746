#include "pid_father.h"
#include <stdio.h>
#include <stdlib.h>

void parent() {
  int pid = getpid();
  while (1) {
    printf("Hello from parent! (pid = %d)\n", pid);
    sleep(1);
  }
}

void child() {
  int pid = getpid();
  for (int i = 0; i < 5; i++) {
    int parent_pid = pid_father(pid);
    printf("Hello from child! (pid = %d, parent_pid = %d)\n", pid, parent_pid);
    sleep(1);
  }
  printf("Child is shutting down, exiting process\n");
  exit(0);
}

void grandson() {
  int pid = getpid();
  while (1) {
    int parent_pid = pid_father(pid);
    printf("Hello from grandson! (pid = %d, parent_pid = %d)\n", pid,
           parent_pid);
    sleep(1);
  }
}

int main() {
  printf("Custom initramfs - pid_father syscall:\n");

  while (1) {
    if (fork() == 0) {
      if (fork() == 0) {
        grandson();
      } else {
        child();
      }
    } else {
      parent();
    }
  }

  printf("Finished kernel init!\n");

  return 0;
}
