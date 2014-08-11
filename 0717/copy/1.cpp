#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student
{
    public:
        Student():name_(""), age_(0), score_(0){}
        Student(const string &name, int age, int score):name_(name), 
        age_(age), score_(score)
        {}
        Student(const Student &other):name_(other.name_),
        age_(other.age_), score_(other.score_){}
        
        void print()
        {
            cout << name_ << " " << age_ << " " << score_ << endl;
        }
    private:
       string name_;
       int age_;
       int score_;
};

int main(int argc, const char *argv[])
{
    Student s1("suqing", 16, 99);
    Student s2;
    Student s3(s1);

    s1.print();
    s2.print();
    s3.print();
    return 0;
}
