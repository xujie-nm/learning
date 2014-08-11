#include "def.h"
#include <stdlib.h>
#include <pthread.h>

void thread_pool_init(pool_t *pool, size_t size)
{
    pool->size_ = size;
    pool->pthreads_ = (pthread_t *)malloc(sizeof(pthread_t) * pool->size_);
    pool->is_started_ = FALSE;
    queue_init(&pool->queue_);
    pthread_mutex_init(&pool->mutex_, NULL);
    pthread_cond_init(&pool->cond_, NULL);
}

void thread_pool_destroy(pool_t *pool)
{
    thread_pool_stop(pool);
    free(pool->pthreads_);
    queue_destroy(&pool->queue_);
    pthread_mutex_destroy(&pool->mutex_);
    pthread_cond_destroy(&pool->cond_);
}

void *thread_pool_thread_func(void *arg)
{
    pool_t *pool = (pool_t *)arg;
    while(1)
    {
        task_t task;
        BOOL ret = thread_pool_get_task_from_queue(pool, &task);
        if(ret == TRUE)
            task.thread_callback(task.arg);
        else
            break;
    }
}

void thread_pool_start(pool_t *pool)
{
    if(pool->is_started_ == FALSE)
    {
        pool->is_started_ = TRUE;
        int i;
        for (i = 0; i < pool->size_; i++) {
            pthread_create(&pool->pthreads_[i], NULL, thread_pool_thread_func, pool);
        }
    }
}

void thread_pool_stop(pool_t *pool)
{
    if(pool->is_started_ == FALSE)
        return;
    pool->is_started_ = FALSE;
    
    pthread_cond_broadcast(&pool->cond_);

    int i;
    for (i = 0; i < pool->size_; i++) {
        pthread_join(pool->pthreads_[i], NULL);
    }
    queue_clear(&pool->queue_);
}

void thread_pool_add_task_to_queue(pool_t *pool, task_t task)
{
    pthread_mutex_lock(&pool->mutex_);
    queue_push(&pool->queue_, task);
    pthread_cond_signal(&pool->cond_);
    pthread_mutex_unlock(&pool->mutex_);
}

BOOL thread_pool_get_task_from_queue(pool_t *pool, task_t *task)
{
    pthread_mutex_lock(&pool->mutex_);
    while(queue_is_empty(&pool->queue_) == TRUE && pool->is_started_ == TRUE)
        pthread_cond_wait(&pool->cond_, &pool->mutex_);

    if(pool->is_started_ == FALSE)
    {
        pthread_mutex_unlock(&pool->mutex_);
        return FALSE;
    }

    *task = queue_top(&pool->queue_);
    queue_pop(&pool->queue_);

    pthread_mutex_unlock(&pool->mutex_);
    return TRUE;
}

BOOL thread_pool_is_started(const pool_t *pool)
{
    return pool->is_started_;
}

size_t thread_pool_get_size_of_queue(const pool_t *pool)
{
    return pool->queue_.size_;
}
