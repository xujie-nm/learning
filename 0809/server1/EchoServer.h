#ifndef ECHO_TCP_SERVER_H
#define ECHO_TCP_SERVER_H 

#include <echo/TcpServer.h>
#include <echo/NonCopyable.h>
#include <echo/ThreadPool.h>
#include "word_qr.h"

class EchoServer : NonCopyable
{
    public:
        EchoServer(const InetAddress &addr);
        void start();
    private:
        void onConnection(const TcpConnectionPtr &conn);
        void onMessage(const TcpConnectionPtr &conn);
        void onClose(const TcpConnectionPtr &conn);

        void compute(const std::string &s, const TcpConnectionPtr &conn);

        TcpServer server_;
        ThreadPool pool_;
        Word_qr ssw;
};



#endif  /*ECHO_TCP_SERVER_H*/
