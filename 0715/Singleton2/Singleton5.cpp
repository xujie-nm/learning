#include <iostream>
#include <string>
#include <vector>
#include "MutexLock.h"
using namespace std;

class Singleton
{
    public:
        static Singleton *getInstance()
        {
            if(pInstance_ == NULL)
            {
               mutex_.lock();
               if(pInstance_ == NULL)
               {
                   sleep(1);
                   pInstance_ = new Singleton;
               }
               mutex_.unlock();
            }
            return pInstance_;
        }
    private:
        Singleton(){}

        static Singleton *pInstance_;
        static MutexLock mutex_;
};


Singleton *Singleton::pInstance_ = NULL;
MutexLock Singleton::mutex_;

void *threadFunc(void *arg)
{
    Singleton *ps = Singleton::getInstance();
    cout << ps << endl;
    return NULL;
}

int main(int argc, const char *argv[])
{
   vector<pthread_t> vec(10);
   for(vector<pthread_t>::iterator it = vec.begin(); it != vec.end(); ++it){
       pthread_create(&*it, NULL, threadFunc, NULL); 
//       cout << *it << endl;
   }

   for(vector<pthread_t>::iterator it = vec.begin(); it != vec.end(); ++it){
       pthread_join(*it, NULL);    
   }
    return 0;
}
