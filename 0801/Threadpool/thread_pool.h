#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include "queue.h"
#include <pthread.h>


class Pool_t
{
    public:
        Pool_t(int size);
        ~Pool_t();
        void start();
        void stop();
        void add_task_to_queue(Task_t);
        BOOL get_task_from_queue(Task_t *);
        BOOL is_started()const;
        int get_size_of_queue()const;

    private:
        int size_;
        pthread_t *pthreads_;
        BOOL is_started_;
        Queue queue_;
        pthread_mutex_t mutex_;
        pthread_cond_t cond_;

};

#endif  /*THREAD_POOL_H_*/
