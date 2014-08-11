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
#include <poll.h>

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

void do_poll(int listenfd);

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("listefd");

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        ERR_EXIT("bind");
    }

    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");


    do_poll(listenfd);

    close(listenfd);
    return 0;
}


void do_poll(int listenfd)
{
    struct pollfd clients[2048];
    int i;
    for (i = 0; i < 2048; i++) {
        clients[i].fd = -1;
    }

    clients[0].fd = listenfd;
    clients[0].events = POLLIN;
    int max = 0;
    int nready;

    while(1)
    {
        nready = poll(clients, max + 1, -1);
        if(nready == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("poll");
        }
        else if(nready == 0)
            continue;
        if(clients[0].revents &POLLIN)
        {
            int peerfd = accept(clients[0].fd, NULL, NULL);
            if(peerfd == -1)
                ERR_EXIT("accept");

            int i = 1;
            for (i = 0; i < 2048; i++) {
                if(clients[i].fd == -1)
                {
                    clients[i].fd = peerfd;
                    clients[i].events = POLLIN;
                    if(i > max)
                        max = i;
                    break;
                }
            }
            if(i == 2048)
            {
                fprintf(stderr, "too many clients\n");
                exit(EXIT_FAILURE);
            }
            if(--nready <= 0)
                continue;
        }

        int i;
        for (i = 0; i <= max; i++) {
            int fd = clients[i].fd;
            if(fd == -1)
                continue;

            char recvbuf[1024] = {0};
            if(clients[i].revents & POLLIN)
            {
                int ret = readline(fd, recvbuf, 1024);
                if(ret == -1)
                    ERR_EXIT("readline");
                else if(ret == 0)
                {
                    close(fd);
                    clients[i].fd = -1;
                    continue;
                }
                printf("recv data: %s", recvbuf);
                writen(fd, recvbuf, strlen(recvbuf));
                if(--nready <= 0)
                    break;
            }
        }
    }
}
