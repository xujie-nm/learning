#ifndef THREAD_H
#define THREAD_H

#include "Condition.h"
#include "MutexLock.h"
#include "classqueue.h"
#include <pthread.h>

class Thread
{
    public:
        Thread();
        Thread(pthread_t tid, int a, Queue* pq):tid_(tid), a_(a), pq_(pq){}
        ~Thread();

        void start();
        static void *producer(void *arg);
        static void *consumer(void *arg);
        void runpro();
        void runcon();
        void join();

    private:
        Queue* pq_;
        pthread_t tid_;
        int a_;//1代表消费者，2代表生产者
};

#endif  /*THREAD_H*/
