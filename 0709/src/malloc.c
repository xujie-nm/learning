#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int **p = (int**)malloc(3*sizeof(int*));
    int i;
    int j;
    for (i = 0; i < 3; i++) {
        p[i] = (int*)malloc(4*sizeof(int));
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            p[i][j] = i*j;
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d\t", p[i][j]);
        }
        printf("\n");
    }
    

    for (i = 0; i < 3; i++) {
        free(p[i]);
    }

    free(p);
    return 0;
}
