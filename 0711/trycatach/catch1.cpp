#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

int main(int argc, const char *argv[])
{
    int num;
    while(1)
    {
       try{
           cin >> num;
           if(num == 1)
           {
               throw std::runtime_error("1");
           }
           else if(num == 2)
           {
               throw std::out_of_range("2");
           }
           else
           {
               throw std::logic_error("3");
           }
       }
       catch(runtime_error &s)
       {
           cout << "runtiom error" <<endl;
           cout << s.what() << endl;
       }
       catch(out_of_range &s)
       {
           cout << "out of range" <<endl;
           cout << s.what() << endl;
       }
       catch(logic_error &s)
       {
           cout << "logic error" <<endl;
           cout << s.what() << endl;
       }
       catch(...)
       {
           cout << "catch a excption" << endl;
       }
       cout << "continue" <<endl;
    }
    return 0;
}
