#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    int i, pid;
    
    for(i = 1; i < 100; i++)
    {
        printf(1, "ticks = %d, ", uptime());
        pid = getpid();
        printf(1, "pid = %d, ", pid);
        printf(1, "name = ");
        getpname();
        printf(1, "\n");
    }
    exit();
}
