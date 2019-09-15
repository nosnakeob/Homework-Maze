#include "LS.hpp"
#include <iostream>

using namespace std;

// ---���겿��---
bool Coordinate::operator==(Coordinate a)
{
    return (this->x == a.x && this->y == a.y);
}

// ---��ջ����---
LinkStack::LinkStack()
{
    stack_top = nullptr;
}

LinkStack::~LinkStack()
{
    Node *p = nullptr;

    while (stack_top != nullptr) //ѭ���ͷ�ջ�ڵ�ռ�
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

void LinkStack::pop()
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
