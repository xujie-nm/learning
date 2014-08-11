#ifndef QUEUE_H_
#define QUEUE_H_ 

#include <stddef.h>

typedef struct q_node {
    int data_;
    struct q_node *next_;
}q_node, *p_node;

typedef struct {
    
    p_node head_;
    p_node tail_;
    size_t size_;
}Queue;

void queue_init(Queue *Q);
void queue_destory(Queue *Q);
void queue_push(Queue *Q, int data);
int queue_top(const Queue *Q);
void queue_pop(Queue *Q);
bool queue_is_empty(const Queue *Q);
void queue_clear(Queue *Q);
size_t queue_get_size(Queue *Q);

#endif  /*QUEUE_H_*/
