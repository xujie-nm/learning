#include "select_t.h"
#include <sys/types.h>
#include <sys/socket.h>

Select_t::Select_t(int listenfd,
                        std::function<void(int, char*) > handle_callback)
                        :listenfd_(listenfd),
                         handle_callback_(handle_callback)
{
    FD_ZERO(&allset_);
    FD_ZERO(&rset_);
    FD_SET(listenfd, &allset_);
 
    for (int i = 0; i < FD_SETSIZE; i++) {
        clients_[i] = -1;
    }
    maxi_ = -1;
    maxfd_ = listenfd;
}

int Select_t::do_wait()
{
    rset_ = allset_;
    int nready;
    do{
        nready = select(maxfd_ + 1, &rset_, NULL, NULL, NULL);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("select");
    nready_ = nready;
    return nready;
}

void Select_t::handle_accept()
{
    if(FD_ISSET(listenfd_, &rset_))
    {
        int peerfd = accept(listenfd_, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accept");
        add_fd(peerfd);
        printf("a client connect: %d\n", peerfd);
        --nready_;
    }
}

void Select_t::handle_data()
{
    if(nready_ == 0)
        return;
    int i;
    for (i = 0; i <= maxi_; ++i) {
        if(FD_ISSET(clients_[i], &rset_))
        {
            int peerfd = clients_[i];
            char recvbuf[1024];
            int ret = readline(peerfd, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                printf("client close \n");
                del_fd(i);
                continue;
            }
            handle_callback_(peerfd, recvbuf);
        }
    }
}

void Select_t::add_fd(int fd)
{
    int i;
    for ( i = 0; i < FD_SETSIZE; i++) {
        if(clients_[i] == -1)
        {
            clients_[i] = fd;
            //test
            printf("add ok : %d\n", fd);
            //test
            if(i > maxi_)
                maxi_ = i;
            break;
        }
    }
    if(i == FD_SETSIZE)
    {
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
    }
    FD_SET(fd, &allset_);
    if(fd > maxfd_)
    {
        maxfd_ = fd;
    }
}

void Select_t::del_fd(int i)
{
    assert(i >= 0 && i < FD_SETSIZE);
    int fd = clients_[i];
    clients_[i] = -1;
    FD_CLR(fd, &allset_);
    close(fd);
}
