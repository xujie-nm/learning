#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    int pid = fork();
    if(pid == 0)
    {
        sleep(10);
        printf("in child pid: %d, ppid: %d\n", getpid(), getppid());
    }
    else
    {
        printf("in parent pid: %d, ppid: %d\n", getpid(), getppid());
    }
    return 0;
}
