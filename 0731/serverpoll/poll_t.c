#include "poll_t.h"
#include <sys/types.h>
#include <sys/socket.h>

void poll_add_fd(poll_t *pol, int fd);
void poll_del_fd(poll_t *pol, int i);

void poll_init(poll_t *pol, int listenfd)
{
    int i;
    for (i = 0; i < 1024; i++) {
        pol->clients_[i].fd = -1;
    }
    pol->clients_[0].fd = listenfd;
    pol->clients_[0].events = POLLIN;
    pol->max_ = 0;
}

int poll_do_wait(poll_t *pol)
{
    int nready;
    do{
        nready = poll(pol->clients_, pol->max_ + 1, -1);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("poll");
    pol->nready_ = nready;
    return nready;
}

void poll_handle_accept(poll_t *pol)
{
    if(pol->clients_[0].revents & POLLIN)
    {
        int peerfd = accept(pol->clients_[0].fd, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accept");
        printf("a client connect: %d\n", peerfd);
        poll_add_fd(pol, peerfd);
    }
} 

void poll_handle_data(poll_t *pol)
{
    int i;
    for (i = 1; i <= pol->max_; i++) {
        if(pol->clients_[i].fd == -1)
            continue;
        if(pol->clients_[i].revents & POLLIN)
        {
            char recvbuf[1024];
            int peerfd = pol->clients_[i].fd;
            int ret = readline(peerfd, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                close(peerfd);
                poll_del_fd(pol, i);
                continue;
            }
            pol->handle_callback_(peerfd, recvbuf);
        }
    }
}

void poll_set_callback(poll_t *pol, void(*handle)(int, char*))
{
    pol->handle_callback_ = handle;
}

void poll_add_fd(poll_t *pol, int fd)
{
    int i;
    for(i = 0; i < 1024; ++i)
    {
        if(pol->clients_[i].fd == -1)
        {
            pol->clients_[i].fd = fd;
            pol->clients_[i].events = POLLIN;
            if(i > pol->max_)
            {
                pol->max_ = i;
            }
            break;
        }
    }
    if(i == 1024)
    {
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
    }
}

void poll_del_fd(poll_t *pol, int i)
{
    assert(i >= 1 && i <= 1024);
    int fd = pol->clients_[i].fd;
    pol->clients_[i].fd = -1;
    close(fd);
}
