#ifndef CONDITION_H_
#define CONDITION_H_ 

#include <unistd.h>
#include <pthread.h>
#include <stdexcept>

class Condition
{
    public:
        Condition()
        {
            if(pthread_cond_init(&cond_, NULL))
            {
                throw std::runtime_error("init cond fail");
            }
        }

        ~Condition()
        {
            if(pthread_cond_destroy(&cond_))
            {
                throw std::runtime_error("destroy cond fail");
            }
        }
   
        void wait(pthread_mutex_t& lock_)
        {
            if(pthread_cond_wait(&cond_, &lock_))
            {
                throw std::runtime_error("cond wait error");
            }
        }

        void signal(Condition &cond)
        {
            if(pthread_cond_signal(&get_cond(cond)))
            {
                throw std::runtime_error("cond signal error");
            }
        }

        pthread_cond_t & get_cond(Condition &cond)
        {
            return cond.cond_;
        }


    private:
        pthread_cond_t cond_;
};

#endif  /*CONDITION_H_*/
