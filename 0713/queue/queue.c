#include "queue.h"

 void queue_init(Queue *Q)
{
    Q->head_ = NULL;
    Q->tail_ = NULL;
}
 void queue_destory(Queue *Q)
{
    queue_clear(Q);
}
 void queue_push(Queue *Q, int data)
{
    p_node cur = (p_node)malloc(sizeof q_node);
    cur->data_ = data;
    cur->next = NULL;
    if(Q->head == NULL)
    {
        Q->head == Q->tail = cur;
    }
    else
    {
        Q->tail.next_ = cur;
        Q->tail = cur;
    }
    ++Q->size_;
}
 int queue_top(const Queue *Q)
{
     if(queue_is_empty(Q))
     {
         return -1;
     }
     return Q->head.data_;
}
 void queue_pop(Queue *Q)
{
     if(queue_is_empty(Q))
     {
         return -1;
     }
     p_node cur = Q->head;
     Q->head = Q->head.next_;
     free(cur);
     --Q->size_;
}
 void queue_clear(Queue *Q)
{
    while(!queue_is_empty(Q))
    {
        queue_pop(Q);
    }
}
 bool queue_is_empty(const Queue *Q)
{
     return Q->head == NULL;
}
 size_t queue_get_size(const Queue *Q)
{
    return Q->size_;
}
