#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  char password[15];
  int ret;
  char *argv2[10] = {"zombie", 0};
  printf(1, "Input password: ");
  gets(password, 15);
  password[strlen(password) - 1] = 0;
  printf(1, "getadmin with password %s\n", password);
  ret = getadmin(password);
  printf(1, "getadmin returned %d\n", ret);
  ret = setmemorylimit(getpid(), 1000000);
  printf(1, "setmemorylimit returned %d\n", ret);
  ret = exec2("zombie", argv2, 10);
  printf(1, "exec2 returned %d\n", ret);
  exit();
  return 0;
}

