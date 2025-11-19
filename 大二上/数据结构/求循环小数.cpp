#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int         data;  
    struct node * next;  
} NODE;  
  
void output( NODE *, int );  
void change( int, int, NODE * );  
  
void output( NODE * head, int kk )  
{   int k=0;  
  
    printf("0.");  
    while ( head->next != NULL && k<kk )  
    {   printf("%d", head->next->data );  
        head = head->next;  
        k ++;  
    }  
    printf("\n");
}  

void change( int n, int m, NODE * head)
{
    if(n >= m)  return;

    NODE **posi = (NODE**)malloc(m * sizeof(NODE*));
    if(posi == NULL)    return;
    for(int i = 0; i < m; i++)
        posi[i] = NULL;
    
    int num = n;
    NODE *newnode;
    NODE *cur = head;
    while(num != 0)
    {
        if(posi[num] != NULL)
        {
            cur->next = posi[num];
            return;
        }

        int x = (num*10)/m;

        newnode = (NODE *)malloc(sizeof(NODE));
        newnode->data = x;
        newnode->next = NULL;
        cur->next = newnode;
        posi[num] = newnode;
        cur = newnode;

        num *= 10;
        num %= m;
    }
}
  
int main()  
{   int n, m,k;  
    NODE * head;  
  
    scanf("%d%d%d", &n, &m, &k);  
    head = (NODE *)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
    change( n, m, head );  
    output( head,k );  
    return 0;  
}