#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Singleton
{
    public:
        static Singleton *getInstance()
        {
            if(pInstance_ == NULL)
            {
                pInstance_ = new Singleton;
            }
            return pInstance_;
        }
    private:
        Singleton(){}
        static Singleton *pInstance_;
};

Singleton *Singleton::pInstance_ = NULL;

int main(int argc, const char *argv[])
{
    Singleton *ps = Singleton::getInstance();
    cout << ps << endl;
    Singleton *ps2 = Singleton::getInstance();
    cout << ps2 << endl;
    
    return 0;
}
