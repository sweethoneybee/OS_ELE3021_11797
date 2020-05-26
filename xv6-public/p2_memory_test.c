#include "types.h"
#include "stat.h"
#include "user.h"

#define N 4096

int main(int argc, char *argv[])
{
  int total = 0;
  int pid = getpid();
  printf(1, "Memory test: pid is %d\n", pid);
  for (;;)
  {
    if (malloc(N) == 0)
    {
      printf(1, "Memory allocation failed.\n");
      exit();
    }
    total += N;
    printf(1, "Memory allocated: %d bytes\n", total);
    sleep(300);
  }
  exit();
  return 0;
}

