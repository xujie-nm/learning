#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool str_sub(const string &str1, const string &str2)
{
    if(str1.size() == str2.size())
    {
        return str1 == str2;
    }
    string::size_type size = (str1.size() < str2.size())?str1.size():str2.size();
    string::size_type i = 0;
    while(i != size)
    {
        if(str1[i] != str2[i])
        {
            return false;
        }
       ++i;
    }
    return true;
}

int main(int argc, const char *argv[])
{
    cout << str_sub("hello", "helli") << endl;
    return 0;
}
