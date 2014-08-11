#include "epoll_t.h"
#include <sys/types.h>
#include <sys/socket.h>

void epoll_add_fd(epoll_t *pol, int fd);
void epoll_del_fd(epoll_t *pol, int fd);

void epoll_init(epoll_t *pol, int listenfd, void(*handler)(int, char*))
{
    if((pol->epollfd_ = epoll_create(2048)) == -1)
        ERR_EXIT("epoll create");
    pol->nready_ = 0;
    pol->listenfd_ = listenfd;
    epoll_add_fd(pol, pol->listenfd_);
    pol->handle_callback_ = handler;
}

void epoll_do_wait(epoll_t *pol)
{
    int nready;
    do{
        nready = epoll_wait(pol->epollfd_, pol->events_, 2048, -1);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("epoll wait");
    pol->nready_ = nready;

}

void epoll_handle(epoll_t *pol)
{
    int i;
    for (i = 0; i < pol->nready_; i++) {
        int fd = pol->events_[i].data.fd;
        if(fd == pol->listenfd_)
        {
            epoll_handle_accept(pol);
        }else
        {
            epoll_handle_data(pol, fd);
        }
    }
}

void epoll_handle_accept(epoll_t *pol)
{
    int peerfd = accept(pol->listenfd_, NULL, NULL);
    if(peerfd == -1)
        ERR_EXIT("accept");
    epoll_add_fd(pol, peerfd);
    printf("a client connect: %d\n", peerfd);
}

void epoll_handle_data(epoll_t *pol, int peerfd)
{
    char recvbuf[1024] = {0};
    int ret = readline(peerfd, recvbuf, 1024);
    if(ret == -1)
        ERR_EXIT("readline");
    else if(ret == 0)
    {
        printf("client close\n");
        epoll_del_fd(pol, peerfd);
        return;
    }
    pol->handle_callback_(peerfd, recvbuf);
}

void epoll_close(epoll_t *pol)
{
    close(pol->listenfd_);
    close(pol->epollfd_);
}

void epoll_add_fd(epoll_t *pol, int fd)
{

    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(epoll_ctl(pol->epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1)
        ERR_EXIT("epoll_ctl_add");

}

void epoll_del_fd(epoll_t *pol, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    if((epoll_ctl(pol->epollfd_, EPOLL_CTL_DEL, fd, &ev)) == -1)
        ERR_EXIT("epoll_ctl_del");
}
