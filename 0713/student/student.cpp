#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student
{
    private:
        string name_;
        int age_;
        int score_;
    public:
        void set_name(const string &name)
        {
            name_ = name;
        }
        //这个
        const string& get_name()const
        {
            return name_;
        }
        //

        string get_name()
        {
            return name_;
        }
        //
        void set_age(int age)
        {
            age_ = age;
        }
        int get_age()const
        {
            return age_;
        }
        void set_score(int score)
        {
            score_ = score;
        }
        int get_score()const
        {
            return score_;
        }
        void print(ostream &os)
        {
            os << name_ << " " << age_ << " " << score_ << endl;
        }
};

int main(int argc, const char *argv[])
{
    Student stu;
    stu.set_name("wsk");
    stu.set_age(20);
    stu.set_score(99);
    stu.print(cout);
    return 0;
}
