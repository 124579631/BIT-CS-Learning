#include <stdio.h>  
#include <stdlib.h>  
typedef struct node  
{   
    int         data;  
    struct node * next;  
} NODE;  
  
NODE * find( NODE * , int * );  
void outputring( NODE * );  
void change( int , int , NODE * );  
void outputring( NODE * pring )  
{   
    NODE * p;  
    p = pring;  
    if ( p == NULL )  
        printf("NULL");  
    else  
        do  
        {   printf("%d", p->data);  
            p = p->next;  
        } while ( p != pring );  
    printf("\n");  
    return;  
}  
  
int main()  
{   int n, m;  
    NODE * head, * pring;  
  
    scanf("%d%d", &n, &m);  
    head = (NODE *)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
  
    change( n, m, head );  
    pring = find( head, &n );  
    printf("ring=%d\n", n);  
    outputring( pring );  
  
    return 0;  
} 

void change(int n, int m, NODE *head)
{
    NODE *cur = head;
    NODE *pos[10000] = {NULL};

    int res = n % m;
    while (res != 0 && pos[res] == NULL)
    {
        pos[res] = cur;
        res *= 10;

        NODE *p = (NODE *)malloc(sizeof(NODE));
        p->data = res / m;
        p->next = NULL;
        cur->next = p;
        cur = p;

        res %= m;
    }

    if (res != 0)
        cur->next = pos[res]->next;

}

NODE *find(NODE *head, int *n)
{
    NODE *slow = head;
    NODE *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (fast == NULL || fast->next == NULL)
    {
        *n = 0;
        return NULL;
    }

    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    NODE *entry = slow;
    int len = 1;
    NODE *p = entry->next;
    while (p != entry) 
    {
        len++;
        p = p->next;
    }
    
    *n = len;
    return entry;
}