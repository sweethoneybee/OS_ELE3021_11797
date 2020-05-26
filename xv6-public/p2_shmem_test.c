#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int pid, parent;
  char *shmem;
  parent = getpid();
  
  if ((pid = fork()) < 0)
  {
    printf(1, "fork failed!\n");
    exit();
  }
  if (pid == 0)
  {
    sleep(100);
    shmem = getshmem(parent);
    printf(1, "A message from the parent process: %s\n", shmem);
    printf(1, "Now this should trigger page fault for the child process.\n");
    strcpy(shmem, "The child process is not allowed to write in the shared memory!");
  }
  else
  {
    shmem = getshmem(parent);
    strcpy(shmem, "This is a message from the parent process");
    wait();
    printf(1, "The parent process should still be able to write.\n");
    strcpy(shmem, "Another message from the parent process");
  }

  exit();
  return 0;
}

