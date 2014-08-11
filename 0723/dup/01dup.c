#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY, 0666);
    if(fd == -1)
    {
        ERR_EXIT("open");
    }

    int fd2 = 5;
    dup2(fd, fd2);
    printf("%d, %d\n", fd, fd2);

    char buf[100] = {0};
    read(fd2, buf, 10);
    printf("buf = %s\n", buf);

    memset(buf, 0, strlen(buf));
    read(fd, buf, 10);
    printf("buf = %s\n", buf);

    close(fd);
    close(fd2);
    return 0;
}
