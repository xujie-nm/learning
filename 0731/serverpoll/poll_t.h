#ifndef POLL_T_H
#define POLL_T_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct{
    struct pollfd clients_[1024];
    int max_;
    int nready_;
//    int maxfd;
    void (*handle_callback_)(int, char*);
} poll_t;

void poll_init(poll_t *pol, int listenfd);
void poll_set_callback(poll_t *pol, void(*handle_callback)(int, char*));
int poll_do_wait(poll_t *pol);
void poll_handle_accept(poll_t *pol);
void poll_handle_data(poll_t *pol);

#endif  /*POLL_T*/
