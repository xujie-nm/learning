#ifndef TCP_CONNECTION_H_
#define TCP_CONNECTION_H_ 

#include "NonCopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Rio.h"
#include <string>
#include <memory>
#include <functional>
#include <unistd.h>
#include <fcntl.h>

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection : private NonCopyable
{
    public:
        typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;

        explicit TcpConnection(int sockfd);
        ~TcpConnection();

        int fd()const
        { return sockfd_.fd(); }

        ssize_t readn(char *usrbuf, size_t n);
        ssize_t readline(char *usrbuf, size_t maxline);
        ssize_t writen(const char *usrbuf, size_t n);
        void sendString(const std::string &s);
        std::string receiveString();
        void shutdown();

    private:
        Socket sockfd_;
        Rio buffer_;
};


#endif  /*TCPCONNECTION_H_*/
