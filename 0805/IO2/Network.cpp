#include "Network.h"

Network::Network(int fd, 
                 void *usrbuf)
    :fd_(fd), usrbuf_(usrbuf)
{}

ssize_t Network::readn(int size)
{
    size_t nleft = size;
    ssize_t nread;
    char *bufp = (char*)usrbuf_;

    while(nleft > 0)
    {
        if((nread = read(fd_, bufp, nleft)) == -1)
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (size - nleft);
}

ssize_t Network::writen(int size)
{
    size_t nleft = size;
    ssize_t nwrite;

    char *bufp = (char*)usrbuf_;

    while(nleft > 0)
    {
        if(nwrite = write(fd_, bufp, nleft) <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            else
                return -1;
        }

        nleft -= nwrite;
        bufp += nwrite;
    }

    return size;
}

ssize_t Network::recv_peek(int size)
{
    int nread;
    while(1)
    {
        nread = recv(fd_, usrbuf_, size, MSG_PEEK);
        if(nread < 0 && errno == EINTR)
            continue;
        if(nread < 0)
            return -1;
        break;
    }

    return nread;
}

ssize_t Network::readline(int size)
{
    int nread;
    int nleft;
    char *ptr;
    int ret;
    int total = 0;

    nleft = size - 1;
    ptr = (char*)usrbuf_;

    while(nleft > 0)
    {
        ret = recv_peek(nleft);
        
        if(ret <= 0)
        {
            return ret;
        }

        nread = ret;
        int i;
        for (i = 0; i < nread; i++) {
            if(ptr[i] == '\n')
            {
                ret = readn(i + 1);
                if(ret != i + 1)
                    return -1;

                total += ret;
                ptr += ret;
                *ptr = 0;
                return total;
            }
        }

        ret = readn(nread);
        if(ret != nread)
        {
            return -1;
        }
        nleft -= nread;
        total += nread;
        ptr += nread;
    }
    *ptr = 0;
    return size - 1;
}
