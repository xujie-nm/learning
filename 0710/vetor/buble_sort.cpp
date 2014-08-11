#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

bool cmp1(int a, int b)
{
    return a > b;
}

void buble_sort(vector<int> &vec, bool (*cmp)(int,int))
{
    auto len = vec.size();
    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = len - 2;  j > i;  j--) {
            if(cmp(vec[j], vec[j - 1]))
                swap(vec[j], vec[j-1]);
        }
        
    }
}

int main(int argc, const char *argv[])
{
   vector<int> ivec;
   srand(10086);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);
   ivec.push_back(rand()%100);

   buble_sort(ivec, cmp1);
   for(auto &item: ivec){
           cout << item << " ";
   }
   cout << endl;
    return 0;
}
