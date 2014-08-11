#ifndef THREAd_H_
#define THREAd_H_
#include <pthread.h>

class Buffer;

class Thread
{
    public:
        Thread(Buffer &buffer):buffer_(buffer), tid_(0){};
        void start();
        static void *threadFunc(void *arg);
        void run();
        void join();
        virtual ~Thread(){};
    protected:
        pthread_t tid_;
        Buffer &buffer_;
};

class ProduceThread : public Thread
{
    public:
        ProduceThread(Buffer &buffer):Thread(buffer){};
        void run();
        virtual ~ProduceThread(){};
        
};

class ConsumeThread : public Thread
{
    public:
        ConsumeThread(Buffer &buffer):Thread(buffer){};
        void run();
        virtual ~ConsumeThread(){};
};

#endif  /*THREAd_H_*/
