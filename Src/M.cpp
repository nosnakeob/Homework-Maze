#include "M.hpp"
#include "LS.hpp"
#include <iostream>
#include <vector>

using namespace std;

// ---迷宫部分---
Maze::Maze()
{
    m = n = 0;
    for (int i = 0; i < MAXSIZE; i++)
        for (int j = 0; j < MAXSIZE; j++)
            is_block[i][j] = is_visited[i][j] = 1;
}

Maze::~Maze()
{
}

void Maze::create()
{
    cout << "Please enter the maze's Length(m), width(n) (m,n < " << MAXSIZE - 5 << "):" << endl;
    cin >> m >> n;

    cout << "Please enter the maze's picture (0:Accessible,1:Blocked):" << endl;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> is_block[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            is_visited[i][j] = is_block[i][j];

    cout << "Complete!!!" << endl;
}

void Maze::draw()
{
    cout << "Let me draw the maze:" << endl;

    cout << "   ";
    for (int i = 1; i <= m; i++)
    {
        cout.width(3);
        cout << i;
    }

    cout << endl;

    for (int i = 1; i <= n; i++)
    {
        cout.width(3);
        cout << i;
        for (int j = 1; j <= m; j++)
        {
            cout.width(3);

            cout << (is_block[i][j] ? "0" : "");
        }
        cout << endl;
    }
}

void Maze::findWaysN()
{
    Coordinate begin, end, now, update; //入口、出口、当前、更新坐标
    vector<Coordinate> paths;           //存储路径
    LinkStack stack;
    bool is_found(0);
    int direction[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; //4个方向

    cout << "Please enter the begining and end (x y|0<x,y<" << MAXSIZE - 5 << ")" << endl;
    cout << "begining:";
    cin >> begin.x >> begin.y;
    cout << "end:";
    cin >> end.x >> end.y;
    cout << "Working..." << endl;

    stack.push(begin);

    while (!stack.isEmpty())
    {
        paths.push_back(now = stack.top()); //记录当前位置
        stack.pop();

        if (now == end) //到达出口   ==重载
        {
            cout << "Find a way:";
            for (vector<Coordinate>::iterator it = paths.begin(); it != paths.end() - 1; it++)
                cout << "(" << it->x << "," << it->y << ") -> ";
            cout << paths.end()->x << paths.end()->y << endl;

            is_found = 1;
            break;
        }

        for (int i = 0; i < 4; i++) //选择方向
        {
            update.x = now.x + direction[i][0];
            update.y = now.y + direction[i][1];

            if (!is_visited[update.x][update.y])
            {
                is_visited[now.x][now.y] = 1;
                stack.push(update);
            }
        }
    }

    if (!is_found)
        cout << "Fail to find a way..." << endl;
}

void Maze::findWaysR()
{
}