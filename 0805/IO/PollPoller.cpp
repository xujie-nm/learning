#include "PollPoller.h"

PollPoller::PollPoller(int listenfd,
                        Callback callback)
    :listenfd_(listenfd),
     callback_(callback)
{
    int i;
    for (i = 0; i < 2048; i++) {
        clients_[i].fd = -1;
    }
    clients_[0].fd = listenfd_;
    clients_[0].events = POLLIN;

    maxi_ = 0;
    nready_ = 0;
}

PollPoller::~PollPoller()
{}

void PollPoller::do_wait()
{
    int nready;
    do{
        nready = poll(clients_, maxi_ + 1, -1);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
    {
        ERR_EXIT("poll");
    }
    nready_ = nready;
}

void PollPoller::handle_accept()
{
    if(clients_[0].revents & POLLIN)
    {
        int peerfd = accept(listenfd_, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accept");
        add_fd(peerfd);
    }
}

void PollPoller::handle_data()
{
    int i;
    char recvbuf[1024];
    for (i = 1; i <= maxi_; i++) 
    {
        int peerfd = clients_[i].fd;
        if(peerfd == -1)
            continue;
        if(clients_[i].revents & POLLIN)
        {
            int ret = readline(peerfd, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                printf("clients close\n");
                del_fd(i);
                continue;
            }
            callback_(peerfd, recvbuf);
        }
    }
}

void PollPoller::add_fd(int fd)
{
   int i;
   for (i = 1; i < 2048; i++) 
   {
        if(clients_[i].fd == -1)
        {
            clients_[i].fd = fd;
            clients_[i].events = POLLIN;
            if(i > maxi_)
                maxi_ = i;
            break;
        }
   }

   if(i == 2048)
   {
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
   }
}

void PollPoller::del_fd(int i)
{
    assert(i >= 1 && i < 2048);
    close(clients_[i].fd);
    clients_[i].fd = -1;
}
