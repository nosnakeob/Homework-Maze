#ifndef M_H
#define M_H

class Maze //迷宫
{
private:
    static const int MAXSIZE = 25;                                 //最大区域
    int m, n;                                                      //长、宽
    bool is_block[MAXSIZE][MAXSIZE], is_visited[MAXSIZE][MAXSIZE]; //图

public:
    Maze();        //初始
    ~Maze();       //销毁
    void create(); //创建
    void draw();   //画图

    // 找路
    void findWaysN(); //非递归
    void findWaysR(); //递归
};

#endif