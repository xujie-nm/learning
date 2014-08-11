#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Person{
    friend bool operator<(const Person &p1, const Person &p2);
    public:
        Person()
            :id_(-1), name_(""), age_(0){
        };
        Person(int id, const string &name, int age)
            :id_(id), name_(name), age_(age){
        }


        void print(){
            cout << "id="<< id_ << " name=" << name_ << " age=" << age_ <<endl;    
        }
    private:
        int id_;
        string name_;
        int age_;
};

bool operator<(const Person &p1, const Person &p2)
{
    return p1.id_ < p2.id_;
}

int main(int argc, const char *argv[])
{
    vector<Person> vec;
    vec.push_back(Person(1, "zhangsan", 34));
    vec.push_back(Person(1, "lisi", 34));
    vec.push_back(Person(1, "wangwu", 34));

    sort(vec.begin(), vec.end());


    return 0;
}
