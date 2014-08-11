#ifndef SELECT_T_H_
#define SELECT_T_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <functional>
#include "network.h"

#include <sys/socket.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

class Select_t
{
    public:
        Select_t(int listenfd,
                 std::function<void(int, char*)>handle_callback);
        int do_wait();
        void handle_accept();
        void handle_data();

    private:
        fd_set allset_;
        fd_set rset_;
        int clients_[FD_SETSIZE];
        int maxi_;
        int maxfd_;
        int nready_;
        int listenfd_;
        std::function<void(int, char*)> handle_callback_;

        void add_fd(int fd);
        void del_fd(int i);
};

#endif  /*SELECT_T_H_*/
