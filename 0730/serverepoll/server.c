#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

ssize_t readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0)
    {
        if((nread = read(fd, bufp, nleft)) == -1)
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }else if(nread == 0)
            break;

        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

ssize_t writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwrite;

    char *bufp = usrbuf;

    while(nleft > 0)
    {
        if((nwrite = write(fd, bufp, nleft)) <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            else 
                return -1;
        }

        nleft -= nwrite;
        bufp += nwrite;
    }
    return n;
}

ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
    int nread;
    while(1)
    {
        nread = recv(sockfd, buf, len, MSG_PEEK);
        if(nread < 0 && errno == EINTR)
        {
            continue;
        }
        if(nread < 0)
            return -1;
        break;
    }
    return nread;
}

ssize_t readline(int sockfd, void *buf, size_t maxline)
{
    int nread;
    int nleft;
    char *ptr;
    int ret;
    int total = 0;

    nleft = maxline -1;
    ptr = buf;
    
    while(nleft > 0)
    {
        ret = recv_peek(sockfd, ptr, nleft);

        if(ret <= 0)
            return ret ;
        nread = ret ;
        int i;
        for (i = 0; i < nread; i++) {
            if(ptr[i] == '\n')
            {
                ret = readn(sockfd, ptr, i + 1);
                if(ret != i+1)
                    return -1;
                total += ret;
                ptr += ret;
                *ptr = 0;
                return total;
            }
        }

        ret = readn(sockfd, ptr, nread);
        if(ret != nread)
            return -1;
        nleft -= nread;
        total += nread;
        ptr += nread;
    }
    *ptr = 0;
    return maxline;
}

void do_epoll(int listenfd);

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("listefd");
    int on = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        ERR_EXIT("SETSOCKOPT");

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        ERR_EXIT("bind");
    }

    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");


    do_epoll(listenfd);

    close(listenfd);
    return 0;
}


void do_epoll(int listenfd)
{
    int epollfd = epoll_create(2048);
    if(epollfd == -1)
        ERR_EXIT("epoll_create");

    struct epoll_event ev;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1)
        ERR_EXIT("epoll_ctl");

    struct epoll_event events[2048];
    int nready;

    while(1)
    {
        nready = epoll_wait(epollfd, events, 2048, -1);
        if(nready == -1)
        {
            if(errno == EINTR)
                continue;
               ERR_EXIT("epoll_wait");
        }

        int i;
        for (i = 0; i < nready; i++) {
            if(events[i].data.fd == listenfd)
            {
                int peerfd = accept(listenfd, NULL,NULL);
                if(peerfd == -1)
                    ERR_EXIT("accept");
                struct epoll_event ev;
                ev.data.fd = peerfd;
                ev.events = EPOLLIN;
                if(epoll_ctl(epollfd, EPOLL_CTL_ADD, peerfd, &ev) == -1)
                    ERR_EXIT("epoll_ctl");
            }
            else
            {
                int peerfd = events[i].data.fd;
                char recvbuf[1024] = {0};
                int ret = readline(peerfd, recvbuf, 1024);
                if(ret == -1)
                    ERR_EXIT("readline");
                else if(ret == 0)
                {
                   
                    printf("client close\n");
                    struct epoll_event ev;
                    ev.data.fd = peerfd;
                    if(epoll_ctl(epollfd, EPOLL_CTL_DEL, peerfd, &ev) == -1)
                        ERR_EXIT("epoll_ctl");
                    close(peerfd);
                    continue;
                }

                printf("recv data : %s", recvbuf);
                writen(peerfd, recvbuf, strlen(recvbuf));
            }
        }
    }
}
