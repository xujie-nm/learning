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
#include <stddef.h>

int main(int argc, const char *argv[])
{
    FILE *fp = fopen("test.txt", "rb");
    if(fp == NULL)
    {
        perror("open");
        exit(-1);
    }
    
    char buf[1024] = {0};
    int ret = fread( buf, 1, 1024, fp);
    if(ret == -1)
    {
        perror("read");
        exit(-1);
    }

    printf("%s\n", buf);
    return 0;
}
