#include "1.h"

typedef int******** int8;

void swap(int8 *a, int8 *b){
    int8 temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, const char *argv[])
{
    int8 i;
    int8 j;
    int8 *a = &i; 
    int8 *b = &j;
    printf("%d\t%d\n", *a, *b);
    swap(a,b);
    printf("%d\t%d", *a, *b);
    return 0;
}
