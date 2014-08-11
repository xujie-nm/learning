#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void handler(int signum)
{
    static int beeps = 0;
    printf("beep\n");
    if(++beeps < 5)
        alarm(1);
    else
        printf("BOOM\n"),
            exit(EXIT_SUCCESS);
}

int main(int argc, const char *argv[])
{
    if(signal(SIGALRM, handler) == SIG_ERR)
         ERR_EXIT("signal");

    alarm(1);
    
    while(1);
    return 0;
}
