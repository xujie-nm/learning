#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0);

typedef struct sockaddr *SA;

void do_service(int peerfd)
{
    char recvbuf[1024] = {0};
    while(1)
    {
        int ret = read(peerfd, recvbuf, 1024);
        if(ret == -1 && errno == EINTR)
        {
             continue ;
        }
        else if(ret == 0)
        {
            close(peerfd);
            break;
        }
        else
        {
            write(peerfd, recvbuf, ret);
        }
    }
}

int main(int argc, const char *argv[])
{
    int listenfd = socket(PF_INET,SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        ERR_EXIT("socket");
    }
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5656);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t len = sizeof servaddr;
    if(bind(listenfd, (SA)&servaddr, len) == -1)
    {
        ERR_EXIT("bind");
    }

    if(listen(listenfd, SOMAXCONN) ==-1)
    {
        ERR_EXIT("listen");
    }

    struct sockaddr_in peeraddr;
    memset(&peeraddr, 0, sizeof peeraddr);
    len = sizeof peeraddr;
    int peerfd = accept(listenfd, (SA)&peeraddr, &len);
    if(peerfd == -1)
    {
        ERR_EXIT("peeraddr");
    }

    do_service(peerfd);

    close(listenfd);


    return 0;
}



















