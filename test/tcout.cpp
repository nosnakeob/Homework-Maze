#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        cout.width(5);
        cout << i << endl;
    }
    return 0;
}