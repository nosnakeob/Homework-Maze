#ifndef M_H
#define M_H
// #include <vector>
#include "LS.hpp"
#include <string>
using namespace std;

class Maze //迷宫
{
private:
    static const int MAXSIZE = 25;                      //最大区域
    int m, n;                                           //长、宽
    int map[MAXSIZE][MAXSIZE], draft[MAXSIZE][MAXSIZE]; //

    void draw(string str);                             //画
    void DFS(Coordinate now, Coordinate end);          //递归
    bool enterCoordinate(string str, Coordinate &coo); //输入坐标、判断合法性
    void outputWay(Node *p);                           //利用递归输出链栈存储坐标

public:
    Maze();        //初始化
    ~Maze();       //销毁
    void create(); //创建
    void draw();   //画图
    // 找路
    void findWaysN(); //非递归
    void findWaysR(); //递归
};

#endif
