#include <iostream>
#include <string>
#include <vector>

using namespace std;

int Min(int a1, int a2, int a3)
{
    if(a1 < a2)
    {
        if(a1 < a3)
            return a1;
        else
            return a3;
    }
    else
    {
        if(a2 < a3)
            return a2;
        else
            return a3;
    }
}

int count = 0;

int LCS(string s1, string s2, int i, int j)
{
    count ++;
    if(i > 0 && j > 0)
    {
        if(s1[i - 1] == s2[j - 1])
            return LCS(s1, s2, i - 1, j - 1);
        else
        {
            int a1 = LCS(s1, s2, i, j - 1);
            int a2 = LCS(s1, s2, i - 1, j);
            int a3 = LCS(s1, s2, i - 1, j - 1);
            return Min(a1, a2, a3) + 1;
        }
    }
    else
        return i > j ? i : j;
}



int main(int argc, const char *argv[])
{

    string x ;
    string y ;

    while(cin >> x >> y)
    {
        cout << x << " " << x.size() << endl;
        cout << y << " " << y.size() << endl;

        cout << "LCS: " << LCS(x, y, x.size(), y.size()) << endl ;
        cout << "times: " << count << endl << endl;
    }

    return 0;
}
