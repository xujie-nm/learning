#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
void do_service(int peerfd)
{
    int ret;
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while(1)
    {
        memset(recvbuf, 0, 1024);
        memset(sendbuf, 0, 1024);
        if(fgets(sendbuf, 1024, stdin) != NULL)
        {
            write(peerfd, sendbuf, strlen(sendbuf));
            ret = read(peerfd, recvbuf, 1024);
            if(ret == -1)
            {
                if(errno == EINTR)
                    continue;
                return;
            }
            else if(ret == 0)
                break;
            printf("recv msg: %s\n", recvbuf);
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
