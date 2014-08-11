#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int val = 10;

int main(int argc, const char *argv[])
{
    int pid = fork();
    if(pid > 0)
    {
        printf("in parent: pid1 = %d, pid2 = %d\n", pid, getpid());
        printf("in parent val = %d\n", val);
        sleep(10);
    }
    else
    {

        printf("in parent: pid1 = %d, pid2 = %d\n", pid, getpid());
        printf("in child val = %d\n", ++val);
        sleep(10);
    }
    return 0;
}
