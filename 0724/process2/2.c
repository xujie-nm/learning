#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_WRONLY | O_CREAT, 0666);
    if(fd == -1)
        ERR_EXIT("open");
    
    int pid = fork();
    
    if(pid > 0)
    {
        sleep(5);
        write(fd, "hello", 5);
    }
    else
    {
        write(fd, "world", 5);
    }

    close(fd);
    return 0;
}
