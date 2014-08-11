#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void handler(int signum)
{
    printf("receive a msg\n");
    alarm(1);
}

int main(int argc, const char *argv[])
{
    if(signal(SIGALRM, handler) == SIG_ERR)
        ERR_EXIT("signal");
    
    
    alarm(3);

    while(1);
    return 0;
}
