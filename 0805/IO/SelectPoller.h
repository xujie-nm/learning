#ifndef SELECTPOLLER_H_
#define SELECTPOLLER_H_

#include "Poller.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <functional>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

class SelectPoller : public Poller
{
    public:

        typedef std::function<void(int, char*)> Callback;

        SelectPoller(int listenfd,
                Callback callback);
        void do_wait();
        void handle_accept();
        void handle_data();

        ~SelectPoller();
    private:
        fd_set allset_;
        fd_set rset_;
        int clients_[FD_SETSIZE];
        int maxi_;
        int maxfd_;
        int nready_;
        int listenfd_;
        Callback callback_;

        void add_fd(int fd);
        void del_fd(int i);
};

#endif  /*SELECTPOLLER_H_*/
