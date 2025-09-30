#include <stdio.h>

#define INIT_LEN 20

typedef struct 
{
    int data[INIT_LEN];
    int len;
}SqList;

void InitList(SqList *L)
{
    L->len = 0;
};



int main()
{
    SqList myList;
    InitList(&myList);


    return 0;
}