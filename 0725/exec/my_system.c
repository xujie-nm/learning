#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int my_system(const char *command)
{
    pid_t pid;
    int status = 0;
    printf("1%s\n", command);
    if(command == NULL)
    {
        return 1;
    }
    if((pid = fork()) < 0)
    {
        ERR_EXIT("fork");
    }else if(pid == 0)
    {
        printf("2%s\n", command);
        execl("/bin/sh", "sh", "-c", command, NULL);
        printf("3%s\n", command);
        ERR_EXIT("execl");
    }else
    {
        while( waitpid(pid, &status, 0) < 0)
        {
            if(errno == EINTR)
                continue;
            else
                status = -1;
                break;
        }
    }
    return status;
}

int main(int argc, const char *argv[])
{
    printf("begini\n");
    int t =  my_system("ls") ;
    printf("end: t =%d\n", t);
    return 0;
}
