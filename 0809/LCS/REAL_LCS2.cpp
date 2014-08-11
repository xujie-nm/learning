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

int LCS(const string &x, const string &y)
{
    int num[x.size() + 1][y.size() + 1];
    //声明一个结果数组
    //int num[100][100];
    for (int i = 0; i <= x.size(); i++) 
    {
        num[i][0] = 100;
    }
    //把数组的第一列置为0；
    for (int i = 0; i <= y.size(); i++) 
    {
        num[0][i] = 100;
    }
    num[0][0] = 0;
    //把数组的第一行置为0；
    for (int i = 1; i <= x.size(); i++) 
    {
        for (int j = 1; j <= y.size(); j++) 
        {
            if(x[i - 1] == y[j - 1])
            {
                num[i][j] = num[i - 1][j - 1];
                //如果字符相等，则对角线相加
            }
            else
            {
                int a1 = num[i][j - 1];
                int a2 = num[i - 1][j];
                int a3 = num[i - 1][j - 1];
                num[i][j] = Min(a1, a2, a3) + 1;
                //如果不相等，则取上面和左边的较大者
            }
        }
    }
   
    for (int i = 0; i <= x.size(); i++) //输出查看数组是否正确
    {
        for (int j = 0; j <= y.size(); j++) 
        {
            cout << num[i][j] << " " ;   
        }
        cout << endl;
    }
    return 0;
}


int main(int argc, const char *argv[])
{
    string x = argv[1];
    string y = argv[2];

    LCS(x, y);

    return 0;
}
