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
    int fd1 = open("test.txt", O_RDONLY, 0666);
    int fd2 = open("test.txt", O_RDONLY, 0666);
    if(fd1 == -1 || fd2 == -1)
    {
        ERR_EXIT("open");
    }

    char buf1[11] ;
    char buf2[11] ;

    int ret1 = read(fd1, buf1, 10);
    int ret2 = read(fd2, buf2, 10);
    if(ret1 == -1 || ret2 == -1)
    {
        ERR_EXIT("read");
    }
    buf1[10] = 0;
    buf2[10] = 0;

    printf("fd1 : %s\n", buf1);
    printf("fd2 : %s\n", buf2);

//    memset(buf1, 0, 10 );
//    memset(buf2, 0, 10 );

     ret1 = read(fd1, buf1, 10);
     ret2 = read(fd2, buf2, 10);
    if(ret1 == -1 || ret2 == -1)
    {
        ERR_EXIT("read");
    }

    printf("fd1 : %s\n", buf1);
    printf("fd2 : %s\n", buf2);
            
    return 0;
}
