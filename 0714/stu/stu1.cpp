#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student{
    public:
        Student():name_("nullname"), age_(-1), score_(-1){}

        Student(const string &name,
                int age,
                int score)
            :name_(name),
            age_(age),
            score_(score){}
            
        void print()
        {
            cout << "not const" << endl;
            cout << name_ << " " << age_ << " " << score_ << endl;
        }
 
        void print()const
        {
            cout << "in const" << endl;
            cout << name_ << " " << age_ << " " << score_ << endl;
        }
    private:
        string name_;
        int age_;
        int score_;
};

int main(int argc, const char *argv[])
{
    Student stu("wsk", 21, 99);
    stu.print();
    const Student stu1("xujie", 21, 90);
    stu1.print();
    Student stu3;
    stu3.print();
    return 0;
}
