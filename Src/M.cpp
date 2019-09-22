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
            map[i][j] = draft[i][j] = 1;
}

Maze::~Maze() //?
{
}

void Maze::create()
{
    while (1)
    {
        cout << "Please enter the maze's length(m), width(n) (0 < m, n < " << MAXSIZE - 5 << "):";
        cin >> m >> n;
        if (m <= 0 || m >= MAXSIZE - 5 || n <= 0 || n >= MAXSIZE - 5)
            cout << "Invalid number! Please enter the line again.\n"
                 << endl;

        else
            break;
    }

    cout << "Please enter the maze's picture (0:O, 1:X):" << endl;

    for (int i = 1; i <= n; i++) //
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] != 1 && map[i][j] != 0) //输入其他东西
            {
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); //清除输入缓冲区的当前行
                cout << "Invalid number! Please enter the line again.\n"
                     << endl;
                j = 0;
            }
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            draft[i][j] = map[i][j];

    cout << "Complete!!!\n"
         << endl;

    draw("maze");
}

void Maze::draw(string str)
{
    cout << "\nLet me draw the " << str << ":" << endl;

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
            switch (map[i][j])
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
bool is_found_way = 0, is_found_direction = 0;

//===非递归===
bool Maze::enterCoordinate(string str, Coordinate &coo)
{
    cout << "Please enter the " << str << "(0 < x <= " << n << ", 0 < y <= " << m << "):";
    cin >> coo.x >> coo.y;

    if (coo.x <= 0 || coo.x > n || coo.y <= 0 || coo.y > m) //越界
        return 0;

    if (map[coo.x][coo.y] == 1) //堵路
        return 0;

    return 1;
}

void Maze::outputWay(Node *p)
{
    if (!p)
        return;

    outputWay(p->next);
    cout << "(" << p->x << "," << p->y << ") -> ";
}

void Maze::findWaysN()
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
        draft[now.x][now.y] = 1; //标记已走坐标

        if (now == end)
        {
            for (Node *p = stack.end(); p; p = p->next) //标记路径
                map[p->x][p->y] = 2;

            draw("map");

            outputWay(stack.end()->next);
            cout << "(" << stack.end()->x << "," << stack.end()->y << ")" << endl;

            is_found_way = 1;
            break;
        }

        is_found_direction = 0;
        for (int i = 0; i < 4; i++) //选择方向
        {
            update.x = now.x + direction[i][0];
            update.y = now.y + direction[i][1];

            if (!draft[update.x][update.y]) //能走
            {
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

//===递归===
vector<Coordinate> paths; //存路径

void Maze::DFS(Coordinate now, Coordinate end)
{
    if (draft[now.x][now.y] == 1) //堵路
        return;

    if (now == end) //到终点
    {
        is_found_way = 1;
        return;
    }

    if (is_found_way) //找到路后不必遍历其他路径
    {
        return;
    }

    draft[now.x][now.y] = 1; //堵住路

    Coordinate update;
    for (int i = 0; i < 4; i++) //找路
    {
        update.x = now.x + direction[i][0];
        update.y = now.y + direction[i][1];
        if (!is_found_way)
            paths.push_back(update);

        DFS(update, end);

        if (!is_found_way)
            paths.pop_back();
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

    paths.push_back(begin);
    DFS(begin, end);

    if (is_found_way)
    {
        for (vector<Coordinate>::iterator it = paths.begin(); it != paths.end(); it++)
            map[it->x][it->y] = 2;

        draw("map");

        for (vector<Coordinate>::iterator it = paths.begin(); it != paths.end() - 1; it++)
            cout << "(" << it->x << "," << it->y << ") -> ";

        cout << "(" << (paths.end() - 1)->x << "," << (paths.end() - 1)->y << ")" << endl;
    }
    else
    {
        cout << "Fail to find a way..." << endl;
    }
}
