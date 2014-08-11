#ifndef INET_ADDRESS_H_
#define INET_ADDRESS_H_

#include "Copyable.h"
#include <netinet/in.h>
#include <string.h>

typedef struct sockaddr SA;

class InetAddress : private Copyable
{
    public:
        explicit InetAddress(uint16_t port);
        InetAddress(const struct sockaddr_in &addr);

        const struct sockaddr_in *getSockAddrInet()const
        { return &addr_;  }
        void setSockAddrInet(const struct sockaddr_in &addr)
        { addr_ = addr;  }

        uint32_t ipNetEndian()const
        { return addr_.sin_addr.s_addr; }
        uint16_t portNetEndian()const
        { return addr_.sin_port;  }

        std::string toIp()const;
        uint16_t toPort()const;

        static InetAddress getLocalAddress(int sockfd);
        static InetAddress getPeerAddress(int sockfd);

    private:
        struct sockaddr_in addr_;
};


#endif  /*INET_ADDRESS_H_*/
