#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void *thread_func(void *arg)
{
    printf("Test........\n");
    pthread_t tid = pthread_self();
    printf("tid = %lu\n", (unsigned long)tid);
    pthread_exit((void*)100);
    printf("Test2.........\n");

    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);

    int status;
    pthread_join(tid, (void**)&status);
    printf("pthread exit code = %d\n", status);
    return 0;
}
