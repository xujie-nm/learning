#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test{
    int a;
    int b;
    char c;
};

int main(int argc, const char *argv[])
{
    int *p = (int*)malloc(2*sizeof(int));
    p[0] = 29;
    p[1] = 31;
    struct test *pt = (struct test*)p;
    printf("%d\n", pt->a);
    printf("%d\n", pt->b);
    printf("%d\n", sizeof(struct test));
    return 0;
}
