#include "M.hpp"
#include "LS.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ---迷宫---
Maze::Maze()
{
    m = n = 0;
    for (int i = 0; i < MAXSIZE; i++)
        for (int j = 0; j < MAXSIZE; j++)
            maze[i][j] = map[i][j] = 1;
}

Maze::~Maze()
{
}

void Maze::create()
{
    cout << "Please enter the maze's length(m), width(n) (m, n < " << MAXSIZE - 5 << "):";
    cin >> m >> n;

    cout << "Please enter the maze's picture (0:O, 1:X):" << endl;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> maze[i][j]; //bug 合法性判断

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            map[i][j] = maze[i][j];

    cout << "Complete!!!\n"
         << endl;

    draw("maze", maze);
}

void Maze::draw(string str, int picture[][MAXSIZE])
{
    cout << "Let me draw the " << str << ":" << endl;

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
            char c;
            switch (picture[i][j])
            {
            case 0: //通路
                c = ' ';
                break;
            case 1: //堵路
                c = 'X';
                break;
            case 2: //走路
                c = 'O';
                break;
            default:
                break;
            }

            cout.width(3);
            cout << c;
        }
        cout << endl;
    }
}

// ---找路---
int direction[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; //4方向
vector<Coordinate> paths;                                //存路径
bool is_found_way = 0, is_found_direction = 0;

bool Maze::enterCoordinate(string str, Coordinate &coo)
{
    cout << "Please enter the " << str << "(0 < x <= " << n << ", 0 < y <= " << m << "):";
    cin >> coo.x >> coo.y;

    if (coo.x <= 0 || coo.x > n || coo.y <= 0 || coo.y > m) //不合法
        return 0;

    if (maze[coo.x][coo.y] == 1) //堵路
        return 0;

    return 1;
}

void Maze::findWaysN() //岔路bug
{
    Coordinate begin, end, now, update;
    LinkStack stack;

    while (!enterCoordinate("beginning", begin))
    {
        cout << "Invalid number! Please try again.\n"
             << endl;
    }

    while (!enterCoordinate("end", end))
    {
        cout << "Invalid number! Please try again.\n"
             << endl;
    }

    stack.push(begin);

    while (!stack.isEmpty())
    {
        now = stack.top();

        if (now == end)
        {
            for (Node *p = stack.begin(); p; p = p->next) //标记路径
                map[p->x][p->y] = 2;

            draw("map", map);

            for (Node *p = stack.begin(); p->next; p = p->next)
            {
                cout << "(" << p->x << "," << p->y << ") -> ";
            }
            cout << "(" << stack.end()->x << "," << stack.end()->y << ")" << endl;

            is_found_way = 1;
            break;
        }

        is_found_direction = 0;
        for (int i = 0; i < 4; i++) //选择方向
        {
            update.x = now.x + direction[i][0];
            update.y = now.y + direction[i][1];

            if (!map[update.x][update.y])//能走
            {
                map[now.x][now.y] = 1;
                stack.push(update);

                is_found_direction = 1;
            }
        }

        if (!is_found_direction)
            stack.pop();
    }

    if (!is_found_way)
        cout << "Fail to find a way..." << endl;
}

void Maze::DFS(Coordinate now, Coordinate end)
{
    paths.push_back(now); //记录现在坐标

    if (now == end) //到终点
    {
        is_found_way = 1;
        return;
    }

    if (map[now.x][now.y]) //此路不通
    {
        paths.pop_back();
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        Coordinate update;
        update.x = now.x + direction[i][0];
        update.y = now.y + direction[i][1];
        map[now.x][now.y] = 1; //堵住路
        DFS(update, end);
    }
}

void Maze::findWaysR()
{
    Coordinate begin, end;

    while (!enterCoordinate("beginning", begin))
    {
        cout << "Invalid number! Please try again.\n"
             << endl;
    }

    while (!enterCoordinate("end", end))
    {
        cout << "Invalid number! Please try again.\n"
             << endl;
    }

    DFS(begin, end);

    if (is_found_way)
    {
        cout << "Find a way:";
        for (vector<Coordinate>::iterator it = paths.begin(); it != paths.end(); it++)
            map[it->x][it->y] = 2;

        draw("map", map);

        for (vector<Coordinate>::iterator it = paths.begin(); it != paths.end() - 1; it++)
            cout << "(" << it->x << "," << it->y << ") -> ";

        cout << "(" << (paths.end() - 1)->x << "," << (paths.end() - 1)->y << ")" << endl;
    }
    else
    {
        cout << "Fail to find a way..." << endl;
    }
}
