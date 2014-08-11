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
    int fd = open("test.txt", O_RDONLY, 0666);
    if(fd == -1)
    {
        perror("open");
        exit(-1);
    }

    close(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);

    char buf[1000];
    fgets(buf, 1000, stdin);
    fputs(buf, stdout);

    close(fd);

    return 0;
}
