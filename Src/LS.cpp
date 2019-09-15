#include "LS.hpp"
#include <iostream>

using namespace std;

// ---坐标部分---
bool Coordinate::operator==(Coordinate a)
{
    return (this->x == a.x && this->y == a.y);
}

// ---链栈部分---
LinkStack::LinkStack()
{
    stack_top = nullptr;
}

LinkStack::~LinkStack()
{
    Node *p = nullptr;

    while (stack_top != nullptr) //循环释放栈节点空间
    {
        p = stack_top->next;
        delete stack_top;
        stack_top = p;
    }
}

void LinkStack::push(Coordinate loc)
{
    Node *p = new Node;

    p->x = loc.x;
    p->y = loc.y;
    p->next = stack_top;

    stack_top = p;
}

void LinkStack::pop() //空bug
{
    Node *p = stack_top->next;
    delete stack_top;
    stack_top = p;
}

Coordinate LinkStack::top()
{
    Coordinate loc;
    loc.x = stack_top->x;
    loc.y = stack_top->y;
    return loc;
}

bool LinkStack::isEmpty()
{
    return stack_top == nullptr;
}

Node *LinkStack::end()
{
    return stack_top;
}
