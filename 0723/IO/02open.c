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
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_EXCL, 0666);
    if(fd == -1)
    {
        perror("open");
        exit(-1);
    }

    char buf[] = "tianjin";
    int ret = write(fd, buf, strlen(buf));
    if(ret == -1)
    {
        perror("write");
        exit(-1);
    }

    close(fd);
    return 0;
}
