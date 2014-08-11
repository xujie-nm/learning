#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/wait.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

#define N 10

void handler(int signum)
{
    pid_t pid;
    while((pid = waitpid(-1, NULL, WNOHANG)) >= 0)//有问题
    {
       // ERR_EXIT("waitpid");
        printf("handler process child %d\n", pid);
        sleep(1);
    }
}

int main(int argc, const char *argv[])
{
    if(signal(SIGCHLD, handler) == SIG_ERR)
        ERR_EXIT("SIGNAL");
    pid_t pid;
    int i;
    static int j = 5;
    for (i = 0; i < N; i++) {
        if((pid = fork()) < 0)
            ERR_EXIT("fork");
        else if(pid == 0)
        {
            printf("hello from child %d\n", getpid());
            if(i == 0)
                sleep(1);
            if(i == 4) 
                sleep(10);
            exit(EXIT_SUCCESS);
        }
        if(i == 5)
            sleep(2);
    }
    printf("hehe\n");

    int n;
    char buf[1024];
    if((n = read(STDIN_FILENO, buf, 1000)) < 0)
        ERR_EXIT("read error");
    printf("parent process input\n");

    while(1)
        ;
    return 0;
}
