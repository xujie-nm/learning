#include "def.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void queue_init(queue *Q)
{
    Q->head_ = NULL;
    Q->tail_ = NULL;
    Q->size_ = 0;
}

void queue_destroy(queue *Q)
{
    queue_clear(Q);
}

void queue_push(queue *Q, task_t data)
{
    p_node pt = (p_node)malloc(sizeof(q_node));
    pt->data_ = data;
    pt->next_ = NULL;
    if(queue_is_empty(Q))
    {
        Q->head_ = Q->tail_ = pt;
    }else
    {
        Q->tail_->next_ = pt;
        Q->tail_ = pt;
    }
    ++Q->size_;
}

void queue_pop(queue *Q)
{
    assert(!queue_is_empty(Q));
    p_node pt = Q->head_;
    Q->head_ = Q->head_->next_;
    free(pt);
    --Q->size_;
}

task_t queue_top(const queue *Q)
{
    assert(!queue_is_empty(Q));
    return Q->head_->data_;
}

void queue_clear(queue *Q)
{
    while(!queue_is_empty(Q))
    {
        queue_pop(Q);
    }
}

BOOL queue_is_empty(const queue *Q)
{
    return Q->head_ == NULL;
}

size_t queue_get_size(const queue *Q)
{
    return Q->size_;
}
