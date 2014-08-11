#ifndef NETWORK_H_
#define NETWORK_H_

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

class Network
{
    public:
        Network(int fd, void*usrbuf);

        ssize_t readn(int size);
        ssize_t writen(int size);
        ssize_t recv_peek(int size);
        ssize_t readline(int size);

    private:
        int fd_;
        void *usrbuf_;

        Network(const Network &);
        void operator=(const Network &);
};

#endif  /*NETWORK_H_*/
