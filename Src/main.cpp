#include <iostream>
#include <cstdlib>
#include "M.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Maze maze;

    maze.create();

    maze.draw();

    maze.findWaysN();

    system("pause");

    return 0;
}