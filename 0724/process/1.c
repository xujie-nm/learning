#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(int argc, const char *argv[])
{
    int i = 0;
    
   int pid =  vfork();
//    vfork();
//    vfork();
    if(pid == 0)
    {
        sleep(3);
        printf("hello, child %d\n", ++i);
    }
    else
    {
        printf("hello, father %d\n", ++i);
        exit(EXIT_SUCCESS);
        
    }
    /*
    if(vfork() >0)
    {
        printf("hello, %d\n", ++i);
    }else
    {
        sleep(1);
        printf("hello, %d\n", ++i);
    }
   */
    return 0;
}
