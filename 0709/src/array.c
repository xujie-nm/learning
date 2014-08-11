#include <stdio.h>
#include <stdlib.h>
#define M 10
#define N 10

typedef struct _array {
    int a_[M][N];
    int m_, n_;
}array;

void array_init(array *a_)
{
    int i, j;
    for (i = 0; i < (*a_).m_; i++) {
        for (j = 0; j < (*a_).n_; j++) {
            (*a_).a_[i][j] = i+j;
        }
    }
 
}

void print(array a_)
{
    int i, j;
    for (i = 0; i < a_.m_; i++) {
        for (j = 0; j < a_.n_; j++) {
            printf("%d  %p\t",a_.a_[i][j], &(a_.a_[i][j]));
        }
        printf("\n");
    }
}


int main(int argc, const char *argv[])
{
    array a_;
    a_.m_ = 3;
    a_.n_ = 4;
    array_init(&a_);
    printf("sizeofint*:%d\tsizeofchar*:%d\n", sizeof(int*), sizeof(char*));
    print(a_);   
    return 0;
}


