#include "EpollPoller.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

EpollPoller::EpollPoller(int listenfd,
                         Callback callback)
    :listenfd_(listenfd),
     callback_(callback)
{
    if((epollfd_ = epoll_create(2048)) == -1)
        ERR_EXIT("epoll_create");
    nready_ = 0;
    add_fd(listenfd_);
}

EpollPoller::~EpollPoller()
{
    close(epollfd_);
    close(listenfd_);
}

void EpollPoller::do_wait()
{
    int nready;
    do{
        nready = epoll_wait(epollfd_, events_, 2048, -1);
    }while(nready == -1 && errno == EINTR);

    if(nready == -1)
        ERR_EXIT("epoll_wait");
    nready_ = nready;
}

void EpollPoller::handle()
{
    int i;
    for (i = 0; i < nready_; i++) 
    {
        int fd = events_[i].data.fd;
        if(fd == listenfd_)
            handle_accept();
        else if(fd >= 0)
            handle_data(fd);
    }
}

void EpollPoller::handle_accept()
{
    int peerfd = accept(listenfd_, NULL, NULL);
    if(peerfd == -1)
        ERR_EXIT("accept");
    add_fd(peerfd);
}

void EpollPoller::handle_data(int peerfd)
{
    char recvbuf[1024];
    int ret = readline(peerfd, recvbuf, 1024);
    if(ret == -1)
        ERR_EXIT("readline");
    else if(ret == 0)
    {
        printf("client close\n");
        del_fd(peerfd);
        return;
    }
    callback_(peerfd, recvbuf);
}

void EpollPoller::add_fd(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1)
        ERR_EXIT("ADD_FD");
}

void EpollPoller::del_fd(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    if(epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &ev) == -1)
        ERR_EXIT("DEL_FD");
}
