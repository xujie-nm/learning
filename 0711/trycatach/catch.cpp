#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

int main(int argc, const char *argv[])
{
    int i = 5;
    int j = 2;
    int res ;
    cout << "before catch" << endl;
    try
    {
        if(j == 0)
        {
            throw exception();
        }
        else
        {
            res = i/j;
            cout << "the res: " << res << endl;
        }

        cout << "hehe" <<endl;
    }
    catch(exception &e)
    {
        cout << "in catch" << endl;
        cout << e.what() << endl;
    }

    cout << "after catch" << endl;
    return 0;
}
