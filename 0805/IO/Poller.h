#ifndef POLLER_H_
#define POLLER_H_

class Poller
{
    public:
        Poller(){};
        virtual void do_wait(){};
        virtual void handle_accept(){};
        virtual void handle_data(){};
    private:
       Poller(const Poller &);
       void operator=(const Poller &);
};

#endif  /*POLLER_H_*/
