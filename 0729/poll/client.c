#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
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

    nleft = maxline - 1;
    ptr = buf;
    while(nleft > 0)
    {
        ret = recv_peek(sockfd, ptr, nleft);

        if(ret <= 0)
            return ret;
        nread = ret;

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

void do_service(int peerfd)
{
    int ret;
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};

    struct pollfd client[2];
    client[0].fd = fileno(stdin);
    client[0].events = POLLIN;
    client[1].fd = peerfd;
    client[1].events = POLLIN;
    int maxi = 1;
    int nready;

    while(1)
    {
        nready = poll(client, maxi + 1, -1);
        if(nready == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("poll");
        }else if(nready == 0)
            continue;

        if(client[0].revents & POLLIN)
        {
            if(fgets(sendbuf, 1024, stdin) == NULL)
            {
                shutdown(peerfd, SHUT_WR);
                client[0].fd = -1;
            }else
            {
                writen(peerfd, sendbuf, strlen(sendbuf));
            }
        }

        if(client[1].revents & POLLIN)
        {
            int ret = readline(peerfd, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                printf("server close\n");
                close(peerfd);
                break;
            }
            printf("recv data: %s", recvbuf);
        }
    }
}

int main(int argc, const char *argv[])
{
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");
    
    struct sockaddr_in peeraddr;
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_port = htons(6666);
    peeraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(peerfd, (struct sockaddr*)&peeraddr, sizeof(peeraddr)) < 0)
        ERR_EXIT("connect");

    do_service(peerfd);

    close(peerfd);
    return 0;
}
