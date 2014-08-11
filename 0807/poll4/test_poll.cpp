#include "TcpConnection.h"
#include "PollPoller.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int get_listen_fd();

void onConnect(const TcpConnectionPtr &conn)
{
    conn->sendString("hello");
}

void onMessage(const TcpConnectionPtr &conn)
{
    char buf[1024];
    conn->readLine(buf, 1024);
    cout << "recv string: " << buf << endl;
    conn->sendString(buf);
}

void onClose(const TcpConnectionPtr &conn)
{
    cout << "Close conn" << endl;
    conn->shutdown();
}
int main(int argc, const char *argv[])
{
    int fd = ::socket(PF_INET, SOCK_STREAM, 0);
    if(fd == -1)
        ERR_EXIT("socket");

    Socket sock(fd);
    InetAddress addr(8989);
    sock.setReusePort();
    sock.bindAddress(addr);
    sock.listen();

    PollPoller poller(sock.fd());
    poller.setConnectionCallback(onConnect);
    poller.setMessageCallback(onMessage);
    poller.setCloseCallback(onClose);
    while(1)
    {
        poller.poll();
        poller.handleAccept();
        poller.handleData();
    }

    return 0;
}

