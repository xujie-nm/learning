#ifndef EPOLLPOLLER_H_
#define EPOLLPOLLER_H_

#include <sys/epoll.h>
#include <functional>
#include "Poller.h"

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

class EpollPoller : public Poller
{
    public:
        typedef std::function<void(int, char*)> Callback;

        EpollPoller(int listenfd,
                    Callback callback);

        void do_wait();
        void handle();
        void handle_accept();
        void handle_data(int peerfd);

        ~EpollPoller();

    private:
        int epollfd_;
        int listenfd_;
        struct epoll_event events_[2048];
        int nready_;
        Callback callback_;

        void add_fd(int fd);
        void del_fd(int fd);
};

#endif  /*EPOLLPOLLER_H_*/
