#include <iostream>
#include <string>
#include <vector>
using namespace std;

int LCS(const string &x, const string &y)
{
    int num[x.size() + 1][y.size() + 1];
    //声明一个结果数组
    //int num[100][100];
    for (int i = 0; i <= x.size(); i++) 
    {
        num[i][0] = 0;
    }
    //把数组的第一列置为0；
    for (int i = 0; i <= y.size(); i++) 
    {
        num[0][i] = 0;
    }
    //把数组的第一行置为0；
    for (int i = 1; i <= x.size(); i++) 
    {
        for (int j = 1; j <= y.size(); j++) 
        {
            if(x[i - 1] == y[j - 1])
            {
                num[i][j] = num[i - 1][j - 1] + 1;
                //如果字符相等，则对角线相加
            }
            else
            {
                int m = num[i][j - 1];
                int n = num[i - 1][j];
                num[i][j] = m > n ? m : n;
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
  
    int length = num[x.size()][y.size()];//最大子序列的长度
    char res[length + 1];//最大结果数组
    int i = x.size();
    int j = y.size();
    cout << "length = " << length << endl;
    while(length > 0)//回硕二维数组num，记录结果数组res
    {
        if(num[i][j] == num[i][ j- 1])
            j = j - 1;//如果现在的值和左边相等左移
        else if(num[i][j] == num[i - 1][j])
            i = i - 1;//如果现在的值和上面的相等上移
        else if(num[i - 1][j - 1] + 1 == num[i][j])
        {
            res[length - 1] = y[j - 1];
            //cout << y[j - 1] << endl;
            --length;
            i--;
            j--;
            if(length == 0)
                break;
        }//如果都不相等，说明该值是子序列的值，加入子序列并向左上角移动字符串长度减1
        //并且如果长度等于0，退出循环
    }

    res[num[x.size()][y.size()]] = '\0';//字符串末尾加'\0'

    cout << res << endl;//输出结果
    
    return 0;
}


int main(int argc, const char *argv[])
{
    string x = argv[1];
    string y = argv[2];

    LCS(x, y);

    return 0;
}
