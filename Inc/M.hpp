#ifndef M_H
#define M_H
// #include <vector>
#include "LS.hpp"
#include <string>
using namespace std;

class Maze //迷宫
{
private:
    static const int MAXSIZE = 25; //最大区域
    int m, n;                      //长、宽
    int maze[MAXSIZE][MAXSIZE], map[MAXSIZE][MAXSIZE];

    void draw(string str, int picture[][MAXSIZE]);     //画
    void DFS(Coordinate now, Coordinate end);          //递归
    bool enterCoordinate(string str, Coordinate &coo); //输入坐标、判断合法性

public:
    Maze();        //初始化
    ~Maze();       //销毁
    void create(); //创建
    // void drawMaze(); //画图
    // 找路
    void findWaysN(); //非递归
    void findWaysR(); //递归
    // void drawMap();   //带路
};

#endif
