#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

struct acc
{
    char id[16];
    char pass[16];
};
int
main(int argc, char *argv[])
{
    int fd;
    struct acc u;
    u.id[0] = 'r';
    u.id[1] = 'o';
    u.id[2] = 'o';
    u.id[3] = 't';
    u.id[4] = 0;
    u.pass[0] = '1';
    u.pass[1] = '2';
    u.pass[2] = '3';
    u.pass[3] = '4';
    u.pass[4] = 0;

    printf(1, "user : %s\n", u.id);
    printf(1, "pass : %s\n", u.pass);
    fd = open("accounts", O_CREATE | O_RDWR);
    if(fd >= 0){
        printf(1, "file success!\n");
    }
    else{
        printf(1, "file failed\n");
        exit();
    }


    int size = sizeof(u);
    if(write(fd, &u, size) != size){
        printf(1, "error: write\n");
        exit();
    }
    printf(1, "write ok\n");

    close(fd);

    
    exit();
}
