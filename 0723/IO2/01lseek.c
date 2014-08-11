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
    int fd = open("test.txt", O_RDWR, 0666);
    if(fd == -1)
    {
        perror("open");
        exit(-1);
    }

    char buf[1024] = {0};
    read(fd, buf, 5);
    printf("%s\n", buf);

    off_t len = lseek(fd, 0, SEEK_CUR);
    printf("offset = %d\n", (int)len);

    memset(buf, 0, strlen(buf));
    read(fd, buf, 10);
    printf("buf : %s\n", buf);

    len = lseek(fd, 0, SEEK_CUR);
    printf("offset : %d\n", (int)len);
    
 //   write(fd, "hello", 5);

    close(fd);

    return 0;
}
