#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

struct Node
{
    char data;
    Node* next;
};

void push(Node* &top, char x)
{
    Node *p = new Node;
    p->data = x;
    p->next = top;
    top = p;
}

char pop(Node* top)
{
    if(top == NULL) return '\0';
    Node *p = top;
    char x = p->data;
    delete p;
    return x;
}

char peek(Node* top)
{
    if(top == NULL) return '\0';
    return top->data;
}

int priority(char op)
{
    
}
int mian()
{


    return 0;
}