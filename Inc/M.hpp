#ifndef M_H
#define M_H
#include <vector>
#include "LS.hpp"

class Maze //迷宫
{
private:
    static const int MAXSIZE = 25;                     //最大区域
    int m, n;                                          //长、宽
    int maze[MAXSIZE][MAXSIZE], map[MAXSIZE][MAXSIZE]; //图、3种状态：0假、1真、2路

    // void draw(int picture[][MAXSIZE]);       //画图
    void DFS(Coordinate now, Coordinate end); //用于递归

public:
    Maze();          //初始
    ~Maze();         //销毁
    void create();   //创建
    void drawMaze(); //画原图
    // 找路
    void findWaysN(); //非递归
    void findWaysR(); //递归
    void leadWay();   //带路
};

#endif