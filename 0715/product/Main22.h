#include "ProduceThread.h"
#include "ConsumeThread.h"
#include "Buffer.h"
#include <iostream>

class Main
{
    public:
        Main():buf_(0), pro_(0), con_(0){}
        Main(int buf, int pro, int con):
            buf_(buf), pro_(pro), con_(con){}
        void start()
        {
            Buffer buffer(buf_);
            ProduceThread *p[pro_];
            ConsumeThread *c[con_];
            for (int i = 0; i < pro_; i++) {
                p[i] = new ProduceThread(buffer);
            }
            for (int i = 0; i < con_; i++) {
                c[i] = new ConsumeThread(buffer);
            }
            for (int i = 0; i < pro_; i++) {
                (*p[i]).start();
            }
            for (int i = 0; i < con_; i++) {
                (*c[i]).start();
            }
            for (int i = 0; i < pro_; i++) {
                (*p[i]).join();
            }
            for (int i = 0; i < con_; i++) {
                (*c[i]).join();
            }
        }

    private:
        int buf_;
        int pro_;
        int con_;
};
