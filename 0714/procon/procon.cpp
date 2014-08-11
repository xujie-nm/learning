#include "queue.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 *
 *
 *
 */

 #define ERR_EXIT(m) \
     do { \
         perror(m);\
         exit(EXIT_FAILURE);\
     }while(0);
#define BUFFERSIZE 5

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;
Queue Q;

void *producer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(queue_get_size(&Q) >= BUFFERSIZE)
        {
            pthread_cond_wait(&empty, &mutex);
        }
        int data = rand()%100;
        queue_push(&Q, data);
        printf("producer a data: %d\n", data);
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        sleep(3);
    }
}
 
void *consumer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(queue_is_empty(&Q))
        {
            printf("wait producer\n");
            pthread_cond_wait(&full, &mutex);
        }
        int data = queue_top(&Q);
        queue_pop(&Q);
        printf("consumer a data: %d\n", data);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
}
 
int main(int argc, const char *argv[])
{
    srand(10086);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    queue_init(&Q);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t1, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    queue_destory(&Q);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
