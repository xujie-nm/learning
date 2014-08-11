#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

struct Student
{
    string name_;
    int age_;
    int score_;

    void print(ostream &os)
    {
        os << "name= " << name_ << "  age= " << age_ << "  score= " << score_ <<endl;
    }
};
/*
int main(int argc, const char *argv[])
{
    ifstream is("test.txt");
    string line;
    string word;
    vector<string> lines;
    vector<string> words;
    while(getline(is, line))
    {
        lines.push_back(line);
        istringstream ss(line);
        while(ss >> word)
        {
            words.push_back(word);
        }
    }
    cout << "the lines is:" << endl;
    for(auto &s1:lines)
    {
        cout << s1 << endl;
    }
    cout << "the words is:" << endl;
    for(auto &s2:words)
    {
        cout << s2 << endl;
    }
    is.close();
    return 0;
}
*/

int main(int argc, const char *argv[])
{
    ifstream is("test.txt");
    string line;
    Student stu;
    vector<Student> svec;
    while(getline(is, line))
    {
        istringstream ss(line);
        ss >> stu.name_ >> stu.age_ >> stu.score_;
        svec.push_back(stu);
    }
    for(auto &s:svec)
    {
        s.print(cout);
    }
    return 0;
}
