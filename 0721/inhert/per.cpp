#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person{
    public:
        Person():name_("none"),
                age_(0){};
        Person(const string &name, int age):
                    name_(name), age_(age){}
        void print()
        {
            cout << name_ << " " << age_ << endl;
        }

        virtual ~Person(){
            cout << name_ << endl;
            cout << "destroy person" << endl;
        };
    private:
        string name_;
        int age_;
        
};

class Student : public Person
{
    public:
        Student():Person(), school_("none"){};
        Student(const string &name, int age, const string &school):
                    Person(name, age),
                    school_(school){}
        void print()
        {
            Person::print();
            cout << school_ << endl;
        }
        virtual ~Student(){
            cout << school_ << endl;
            cout << "destroy student" << endl;
        };
    private:
        string school_;
        
};

int main(int argc, const char *argv[])
{

    cout << endl;
    Person p1("zhangsan", 21);
    Student *str = (Student*)&p1;
    str->print();

    cout << endl;
    Student s1("lisi", 23, "wangdao");
    Person *ptr = &s1;
    ptr->print();
    
    cout << endl;
    Student *str1 = (Student*)ptr;
    str1->print();
    
    return 0;
}
