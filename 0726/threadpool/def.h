#ifndef DEF_H_
#define DEF_H_

#include <pthread.h>
#include <stddef.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct{
    void (*thread_callback)(void *);
    void *arg;
}task_t;

typedef struct q_node{
    task_t data_;
    struct q_node *next_;
}q_node, *p_node;

typedef struct{
    p_node head_;
    p_node tail_;
    size_t size_;
}queue;

typedef struct{
    size_t size_;
    pthread_t *pthreads_;
    BOOL is_started_;
    queue queue_;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
}pool_t;

void queue_init(queue *);
void queue_destroy(queue *);
void queue_push(queue *, task_t);
void queue_pop(queue *);
void queue_clear(queue *);
task_t queue_top(const queue *);
BOOL queue_is_empty(const queue *);
size_t queue_get_size(const queue *);

void thread_pool_init(pool_t *, size_t size);
void thread_pool_destroy(pool_t *);
void thread_pool_start(pool_t *);
void thread_pool_stop(pool_t *);
void thread_pool_add_task_to_queue(pool_t *, task_t);
BOOL thread_pool_get_task_from_queue(pool_t *, task_t *);
BOOL thread_pool_is_started(const pool_t *);
size_t thread_pool_get_size_of_queue(const pool_t *);

#endif  /*DEF_H_*/
