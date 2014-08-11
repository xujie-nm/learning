#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_once_t once_ctrl = PTHREAD_ONCE_INIT;

void test()
{
    printf("test once.....\n");
}

void* thread_func(void *arg)
{
    pthread_detach(pthread_self());
    pthread_once(&once_ctrl, test);
    printf("hello = %lu\n", (long unsigned)pthread_self());
    return NULL;

}

int main(int argc, const char *argv[])
{
    pthread_t pth[10];
    int i;
    for (i = 0; i < 10; i++) {
        pthread_create(&pth[i], NULL, thread_func, NULL);
    }

    while(1);
    return 0;
}
