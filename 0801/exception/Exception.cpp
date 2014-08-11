#include "Exception.h"
#include <stdlib.h>
#include <execinfo.h>

Exception::Exception(const char *s)
    :message_(s)
{
    fillStackTrace();
}

Exception::Exception(const std::string &s)
    :message_(s) 
{
    fillStackTrace();
}

Exception::~Exception() throw()
{
}

const char *Exception::what() const throw()
{
    return message_.c_str();
}

void Exception::fillStackTrace()
{
    const int len = 200;
    void* buffer[len];
    int nptrs = ::backtrace(buffer, len);

    char**strings = ::backtrace_symbols(buffer, nptrs);
    if(strings)
    {
        int i;
        for (i = 0; i < nptrs; i++) {
            stack_.append(strings[i]);
            stack_.push_back('\n');
        }
        free(strings);
    }
}

const char *Exception::stackTrace()const throw()
{
    return stack_.c_str();
}
