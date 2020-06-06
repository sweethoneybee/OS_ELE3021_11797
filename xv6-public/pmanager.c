#include "types.h"
#include "user.h"
#include "fcntl.h"

int fork1(void);  // Fork but panics on failure.
void panic(char*);
char* strcpy2(char *s, const char *t)
{
    char *os;
    os = s;
    while((*s++ = *t++) != 0 && *(s-1) != ' ')
        ;
    s[strlen(s) - 1] = 0;
    return os;
}
char password[15];
// Execute cmd.  Never returns.
void
runcmd(char *buf)
{
    char exe[100];
    char arg1[100];
    char arg2[100];
    memset(exe, 0, 100);
    memset(arg1, 0, 100);
    memset(arg2, 0, 100);
    // exit
    if(strcmp(buf, "exit") == 0){
        printf(1, "GOOD BYE!\n");
        exit();
    }
    
    // list
    else if(strcmp(buf, "list") == 0){
        printproclist();
    }

    // kill
    else if(buf[0] == 'k'){
        strcpy2(exe, buf);

        if(strcmp(exe, "kill") != 0)
            return;
        int pid;
        strcpy(arg1, &buf[5]);
        pid = atoi(arg1);
//        printf(1, "kill %d\n", pid);

        if(pid == 0){
            printf(1, "kill failed!\n");
            return;
        }
        int ret;
        ret = kill(pid);
        if(ret == 0)
            printf(1, "kill success!\n");
        else
            printf(1, "kill failed!\n");
        return;
    }

    // execute 
    else if(buf[0] == 'e'){
        strcpy2(exe, buf);

        if(strcmp(exe, "execute") != 0)
            return;
        int stacksize;
        strcpy2(arg1, &buf[8]);        
        strcpy(arg2, &buf[7 + strlen(arg1) + 2]);
       
        stacksize = atoi(arg2);
//        printf(1, "execute %s %d\n", arg1, stacksize);

        //char *argv2[10] = {arg1, 0};
        if(fork1() == 0){
            getadmin(password);
            char arg3[100];
            char* argv[10];
            memset(arg3, 0, 100);
            memset(argv, 0, 10);

            strcpy(arg3, arg1);
            argv[0] = arg3;
            argv[1] = 0;

            exec2(argv[0], argv, stacksize);

            printf(1, "execute <%s> <%d> failed!\n", argv[0], stacksize);
            exit(); // Exec failed.
        }
        return;
    }

    // memlim
    else if(buf[0] == 'm'){
        strcpy2(exe, buf);

        if(strcmp(exe, "memlim") != 0)
            return;
        int pid, limit;
        strcpy2(arg1, &buf[7]);
        pid = atoi(arg1);

        strcpy(arg2, &buf[6 + strlen(arg1) + 2]);
        limit = atoi(arg2);
 //       printf(1, "memlim %d %d\n", pid, limit);

        int ret;
        ret = setmemorylimit(pid, limit);
        if(ret == 0)
            printf(1, "setmemorylimit success!\n");
        else
            printf(1, "setmemorylimit failed!\n");
        return;
    }
    return;
}

int
getcmd(char *buf, int nbuf)
{
  printf(2, "> ");
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  
  buf[strlen(buf) - 1] = 0;
  return 0;
}

int
main(void)
{
  static char buf[100];
  
  int ret;
  printf(1, "Input password: ");
  gets(password, 15);
  password[strlen(password) - 1] = 0;
  ret = getadmin(password);
  if(ret != 0){
      printf(1, "Wrong password. exit()\n");
      exit();
  }

  printf(1, "[Process Manager]\n\n");
  // Read and run input commands.
  while(getcmd(buf, sizeof(buf)) >= 0){
      runcmd(buf);
  }
  exit();
}
void
panic(char *s)
{
      printf(2, "%s\n", s);
        exit();
}

int
fork1(void)
{
  int pid;

  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}


