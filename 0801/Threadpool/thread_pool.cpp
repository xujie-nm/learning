#include "thread_pool.h"
#include "queue.h"
#include <stdlib.h>
//#include <pthread.h>

Pool_t::Pool_t(int size)
{
    size_ = size;
    pthreads_ = (pthread_t *)malloc(sizeof(pthread_t)*size_);
    is_started_ = FALSE;
    pthread_mutex_init(&mutex_, NULL);
    pthread_cond_init(&cond_, NULL);
}

Pool_t::~Pool_t()
{
    stop();
    free(pthreads_);
    pthread_mutex_destroy(&mutex_);
    pthread_cond_destroy(&cond_);
}

void *thread_func(void *arg)
{
    Pool_t *pool = (Pool_t *)arg;
    while(1)
    {
        Task_t task;
        BOOL ret = pool->get_task_from_queue(&task);
        if(ret == TRUE)
            task.thread_callback(task.arg);
        else
            break;
    }
}

void Pool_t::start()
{
    if(is_started_ == FALSE)
    {
        is_started_ = TRUE;
        int i;
        for (i = 0; i < size_; i++) {
            pthread_create(&pthreads_[i], NULL, thread_func, this);
        }
    }
}

void Pool_t::stop()
{
    if(is_started_ == FALSE)
        return;
    is_started_ = FALSE;
    
    pthread_cond_broadcast(&cond_);
    int i;
    for (i = 0; i < size_; i++) {
        pthread_join(pthreads_[i], NULL);
    }
    queue_.clear();
}

void Pool_t::add_task_to_queue(Task_t task)
{
    pthread_mutex_lock(&mutex_);
    queue_.push(task);
    pthread_cond_signal(&cond_);
    pthread_mutex_unlock(&mutex_);
}

BOOL Pool_t::get_task_from_queue(Task_t *task)
{
    pthread_mutex_lock(&mutex_);
    while((queue_.is_empty() == TRUE) && (is_started_ == TRUE))
        pthread_cond_wait(&cond_, &mutex_);

    if(is_started_ == FALSE)
    {
        pthread_mutex_unlock(&mutex_);
        return FALSE;
    }
    *task = queue_.top();
    queue_.pop();

    pthread_mutex_unlock(&mutex_);
    return TRUE;
}

BOOL Pool_t::is_started()const
{
    return is_started_;
}

int Pool_t::get_size_of_queue()const
{
    return queue_.get_size();
}
