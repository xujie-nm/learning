#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"

void task_func(void *arg)
{
    int t = (int)arg;
    printf("%d\n", t * t);
}

int main(int argc, const char *argv[])
{
    pool_t pool;
    thread_pool_init(&pool, 4);
    thread_pool_start(&pool);

    srand(100);
    while(1)
    {
        sleep(1);
        task_t tsk;
        tsk.thread_callback = task_func;
        tsk.arg = (void*)(rand() % 100);
        thread_pool_add_task_to_queue(&pool, tsk);
    }

    thread_pool_stop(&pool);
    thread_pool_destroy(&pool);
    return 0;
}
