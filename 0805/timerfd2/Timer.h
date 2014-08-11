#ifndef TIMER_H_
#define TIMER_H_

#include "NonCopyable.h"
#include <functional>
#include <sys/timerfd.h>

class Timer : NonCopyable
{
    public:
        typedef std::function<void()> TimeCallback;
        Timer();
        ~Timer();

        void setTimer(int val, int interval);
        void setTimerCallback(const TimeCallback &);
        void runTimer();
        void cancelTimer();

    private:
        int timerfd_;
        struct itimerspec howlong_;
        TimeCallback timeCallback_;
        bool isStarted_;
};

#endif  /*TIMER_H_*/
