#include <iostream>
#include <string>
#include <vector>
#include "thread_pool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void task_func(void *arg)
{
    int t = (int)arg;
    printf("%d\n", t * t);
}

int main(int argc, const char *argv[])
{
    Pool_t pool(4);
    pool.start();

    srand(100);
    while(1)
    {
        sleep(1);
        Task_t tsk;
        tsk.thread_callback = task_func;
        tsk.arg = (void*)(rand() % 100);
        pool.add_task_to_queue(tsk);
    }

    pool.stop();


    return 0;
}
