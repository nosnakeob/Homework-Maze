#ifndef LS_H
#define LS_H

class Coordinate //����
{
public:
    int x, y;

    bool operator==(Coordinate a); //����==
};

struct Node //��ջ���
{
    int x, y;
    Node *next;
};

class LinkStack //��ջ
{
private:
    Node *stack_top;

public:
    LinkStack();               //��ʼ��
    ~LinkStack();              //����
    void push(Coordinate loc); //��ջ
    void pop();                //��ջ
    Coordinate top();          //ȡ��ֵ
    bool isEmpty();            // �п�
};

#endif