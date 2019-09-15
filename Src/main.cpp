#include <iostream>
#include <cstdlib>
#include "M.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // freopen("test.in", "r", stdin);

    Maze maze;

    maze.create();

    cout << endl;

    maze.findWaysN();

    // fclose(stdin);
    system("pause");

    return 0;
}