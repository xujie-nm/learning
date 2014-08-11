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

void do_service(int peerfd)
{
    int ret;
    char recvbuf[1024];
    printf("connected\n");
    while(1)
    {
        ret = readline(peerfd, recvbuf, 1024);
        if(ret == 0)
        {
            close(peerfd);
            break;
        }
        printf("recv: %s", recvbuf);
        writen(peerfd, recvbuf, strlen(recvbuf));
    }
}

void handler()
{
    while(waitpid(-1, NULL, WNOHANG) > 0)
        ;
    return;
}

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    if(signal(SIGCHLD, handler) == SIG_ERR)
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

    while(1)
    {
        struct sockaddr_in peeraddr;
        memset(&peeraddr, 0, sizeof(peeraddr));
        socklen_t len = sizeof peeraddr;
        int peerfd = accept(listenfd, (struct sockaddr*)&peeraddr, &len);
        if(peerfd == -1)
            ERR_EXIT("accept");
        pid_t pid;
        if((pid = fork()) < 0)
            ERR_EXIT("fork");
        else if(pid == 0)
        {
            close(listenfd);
            do_service(peerfd);
            exit(EXIT_SUCCESS);
        }
        close(peerfd);
    }

    close(listenfd);
    return 0;
}
