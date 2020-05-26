#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    printf(1, "input password\n");
    char password[15];
    gets(password, 15);
    password[strlen(password) - 1] = 0;

    int correct = 0;
    correct = getadmin(password);
    printf(1, "getadmin result: %d\n", correct);

    exit();
}
