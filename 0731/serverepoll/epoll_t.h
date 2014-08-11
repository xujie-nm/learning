#ifndef E_POLL_T_H
#define E_POLL_T_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct{

    int epollfd_;
    int listenfd_;
    struct epoll_event events_[2048];
    int nready_;
    void(*handle_callback_)(int, char *);

} epoll_t;

void epoll_init(epoll_t *pol, 
               int listenfd,
               void(*handler)(int, char *));

void epoll_do_wait(epoll_t *pol);

void epoll_handle(epoll_t *pol);

void epoll_handle_accept(epoll_t *pol);

void epoll_handle_data(epoll_t *pol, int fd);

void epoll_close(epoll_t *pol);

#endif  /*POLL_T*/
