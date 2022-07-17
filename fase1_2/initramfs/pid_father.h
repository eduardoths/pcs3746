#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>

#define __NR_pid_father 452

long pid_father(int pid) { return syscall(__NR_pid_father, pid); }
