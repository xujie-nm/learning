#include "queue.h"
#include <stdlib.h>
#include <assert.h>

void queue_init(Queue *Q)
{
    Q->head_ = NULL;
    Q->tail_ = NULL;
    Q->size_ = 0;
}

void queue_destory(Queue *Q)
{
    queue_clear(Q);
    //free(Q);
}

bool queue_is_empty(const Queue *Q)
{
    return Q->head_ == NULL;
}

void queue_push(Queue *Q, int data)
{
    p_node pt = (p_node)malloc(sizeof(q_node));
    pt->data_ = data;
    pt->next_ = NULL;
    if(Q->head_ == NULL)
    {
        Q->head_ = pt;
        Q->tail_ = pt;
    }
    else
    {
        Q->tail_->next_ = pt;
        Q->tail_ = pt;
    }
    ++Q->size_;
}

int queue_top(const Queue *Q)
{ 
    assert(!queue_is_empty(Q));
    return Q->head_->data_;
}

void queue_pop(Queue *Q)
{
    assert(!queue_is_empty(Q));
    p_node pcur = Q->head_;
    Q->head_ = Q->head_->next_;
    free(pcur);
    --Q->size_;
}


void queue_clear(Queue *Q)
{
    while(!queue_is_empty(Q))
    {
        queue_pop(Q);
    }
}

size_t queue_get_size(Queue *Q)
{
    return Q->size_;
}

