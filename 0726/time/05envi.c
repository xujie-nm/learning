#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char **environ;

int main(int argc, const char *argv[])
{
    printf("SHELL = %s\n", getenv("SHELL"));
    
    return 0;
}
