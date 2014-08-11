#include <iostream>
#include <string>
#include <vector>
using namespace std;

int LCS(string x, string y, int i, int j)
{
    if(i > 0 && j > 0)
    {
        if(x[i - 1] == y[j - 1])
            return LCS(x, y, i - 1, j - 1) + 1;
        else
        {
            int m = LCS(x, y, i - 1, j);
            int n = LCS(x, y, i, j - 1);
            return (m>n?m:n);
        }
    }
    else if(i == 0 || j == 0)
        return 0;
}

int main(int argc, const char *argv[])
{
    string x = argv[1];
    string y = argv[2];

    cout << x.size() << "  " << y.size() << endl;
    cout << LCS(x, y, x.size(), y.size()) << endl;;
    return 0;
}
