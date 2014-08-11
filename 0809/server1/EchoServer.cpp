#include "EchoServer.h"
#include <iostream>
#include <string>
using namespace std;
using namespace placeholders;

EchoServer::EchoServer(const InetAddress &addr)
    :server_(addr),
     pool_(1000, 4),
     ssw("out.txt")
{
    server_.setConnection(bind(&EchoServer::onConnection, this, _1));
    server_.setMessage(bind(&EchoServer::onMessage, this, _1));
    server_.setClose(bind(&EchoServer::onClose, this, _1));
}

void EchoServer::start()
{
    pool_.start();
    server_.start();
}

void EchoServer::onConnection(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port: "
        << conn->getPeerAddr().toPort() << endl;
    conn->send("Hello, welcome to Echo Server!!!\r\nplease input the search word :\r\n");
}


void EchoServer::onMessage(const TcpConnectionPtr &conn)
{
    string s(conn->receive());
    cout << "the search word: " << s << endl;
    pool_.addTask(bind(&EchoServer::compute, this, s, conn));
}

void EchoServer::compute(const std::string &word, const TcpConnectionPtr &conn)
{
    char s1[50];
    int i = 0;
    while(word[i] != '\r' && word[i] != '\n')
    {
        s1[i] = word[i];
        i++;
    }

    s1[i] = '\0';
    //
    //
    ssw.set_word(s1);
    int wordcount;
    int linecount;
    vector<string> lines;
    wordcount = ssw.result(lines, linecount);

    for(vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        conn->send((*it)) ; 
        conn->send("\r\n\r\n");
    }
    ostringstream os;
    os << "the word count is  " << wordcount << endl << 
        "the line count is  " << linecount << endl;
    string s2 = os.str();
    conn->send(s2);

}

void EchoServer::onClose(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port: "
        << conn->getPeerAddr().toPort() << "Close" << endl;
    conn->shutdown();
}



