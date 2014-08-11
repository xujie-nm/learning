#include "EchoServer.h"
#include <iostream>
#include <string>
#include <ctype.h>
#include <sstream>
using namespace std;
using namespace placeholders;

EchoServer::EchoServer(const InetAddress &addr)
    :server_(addr),
     pool_(1000, 4),
     ssw_("out.txt")
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
    conn->send("Hello, welcome to Echo Server!!!\r\n");
}


void EchoServer::onMessage(const TcpConnectionPtr &conn)
{
    cout << "on message" << endl;
    string s(conn->receive());
  //  string s;
    char s1[100];
    int i = 0;
    while(s[i] != '\r' && s[i] != '\n')
    {
        s1[i] = s[i];
        i++;
    }
    s1[i] = '\0';
    cout << s1 << endl;


   /* 
    for(string::iterator it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << endl;    
        if(*it == '\r' || *it == '\n')
            *it = '\0';
    }
    */
    //ssw_.set_word(s1);
    pool_.addTask(bind(&EchoServer::compute, this, s1, conn));
    //compute(s, conn);
}

void EchoServer::compute(const std::string &s1, const TcpConnectionPtr &conn)
{
    ssw_.set_word(s1);
    int wordcount;
    int linecount;
    vector<string> lines;

   //cout << lines.size() <<"1" << endl;
    wordcount = ssw_.result(lines, linecount);
   // 
   // cout << lines.size()  << "2" << endl;
    for(vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        conn->send((*it));
        conn->send("\r\n\r\n");
    }

    cout << lines.size() << "3" << endl;
   // cout << wordcount << endl;
   // cout << linecount << endl;
    ostringstream ss1;
    string s2;
    ss1 << endl << "the word count is " << wordcount << endl;

    ss1 << endl << "the line count is " << linecount << endl;
    s2 = ss1.str();
    conn->send(s2);

}

void EchoServer::onClose(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port: "
        << conn->getPeerAddr().toPort() << "Close" << endl;
    conn->shutdown();
}



