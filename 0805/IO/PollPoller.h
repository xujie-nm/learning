#ifndef POLLPOLLER_H_
#define POLLPOLLER_H_

#include "Poller.h"
#include "network.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <functional>

#include <poll.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

class PollPoller : public Poller
{
    public:
        typedef std::function<void(int, char*)> Callback;
        PollPoller(int listenfd,
                    Callback callback);

        void do_wait();
        void handle_accept();
        void handle_data();

        ~PollPoller();

    private:
        struct pollfd clients_[2048];
        int listenfd_;
        int maxi_;
        int nready_;
        Callback callback_;

        void add_fd(int fd);
        void del_fd(int i);
};

#endif  /*POLLPOLLER_H_*/
