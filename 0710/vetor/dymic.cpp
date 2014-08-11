#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    int **p = new int*[3];
    int i;
    for (i = 0; i < 3; i++) {

        p[i] = new int[4];
        
    }

    int j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            p[i][j] = i+j;
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            cout << p[i][j] << " ";
        }
        cout << endl;
    }

    for (i = 0; i < 3; i++) {
        delete []p[i];
    }

    delete []p;


     
    return 0;
}
