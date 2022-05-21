#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>

#define __NR_hello_world 451

long hello_world() { return syscall(__NR_hello_world); }
