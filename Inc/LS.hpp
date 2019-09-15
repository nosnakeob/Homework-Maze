#ifndef LS_H
#define LS_H

class Coordinate //坐标
{
public:
    int x, y;

    bool operator==(Coordinate a); //重载==
};

struct Node //链栈结点
{
    int x, y;
    Node *next;
};

class LinkStack //链栈
{
private:
    Node *stack_base, *stack_top; //base用来遍历

public:
    LinkStack();               //初始化
    ~LinkStack();              //销毁
    void push(Coordinate loc); //入栈
    void pop();                //出栈
    Coordinate top();          //取顶值
    bool isEmpty();            // 判空
    Node *end();               //取顶指针
};

#endif