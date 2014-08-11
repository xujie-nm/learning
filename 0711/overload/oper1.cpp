#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Student
{
    string name_;
    int age_;
    double score_;
    bool operator< (const Student &stu)const
    {
        if(score_ != stu.score_)
        {
            return score_ < stu.score_;
        }
        else if(name_ != stu.name_)
        {
            return name_ < stu.name_ ;
        }
        return age_ < stu.age_;
    }
};

int main(int argc, const char *argv[])
{
    Student arr[3] ={
        {"we", 19, 61},
        {"we", 20, 61},
        {"we", 21, 61}
    };

    sort(arr, arr+3);
    
    for (int i = 0; i < 3; i++) {
        cout << arr[i].name_ << " " << arr[i].age_ << " " << arr[i].score_ << endl;
    }

   
    return 0;
}
