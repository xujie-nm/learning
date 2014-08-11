#include "TcpServer.h"
#include <iostream>
#include <string>
using namespace std;

void onConnect(const TcpConnectionPtr &conn)
{
    conn->sendString("hello\r\n");
    conn->sendString("the TCP Connection will be closed\r\n");
}

void onMessage(const TcpConnectionPtr &conn)
{
    string recv = conn->receiveString();
    cout << "recv data" << recv;
    conn->sendString(recv);
}

int main(int argc, const char *argv[])
{
    InetAddress addr(8989);
    TcpServer server(addr);
    server.setConnection(&onConnect);
    server.setMessage(&onMessage);
    server.start();
    return 0;
}
