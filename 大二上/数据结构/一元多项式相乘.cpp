/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int coef, exp;
    struct node *next;
} NODE;

void multiplication(NODE *, NODE *, NODE *);
void input(NODE *);
void output(NODE *);

void input(NODE *head)
{
    int flag, sign, sum, x;
    char c;

    NODE *p = head;

    while ((c = getchar()) != '\n')
    {
        if (c == '<')
        {
            sum = 0;
            sign = 1;
            flag = 1;
        }
        else if (c == '-')
            sign = -1;
        else if (c >= '0' && c <= '9')
        {
            sum = sum * 10 + c - '0';
        }
        else if (c == ',')
        {
            if (flag == 1)
            {
                x = sign * sum;
                sum = 0;
                flag = 2;
                sign = 1;
            }
        }
        else if (c == '>')
        {
            p->next = new NODE();
            p->next->coef = x;
            p->next->exp = sign * sum;
            p = p->next;
            p->next = NULL;
            flag = 0;
        }
    }
}

void output(NODE *head)
{
    while (head->next != NULL)
    {
        head = head->next;
        printf("<%d,%d>,", head->coef, head->exp);
    }
    printf("\n");
}

int main()
{
    NODE *head1, *head2, *head3;

    head1 = new NODE();
    input(head1);

    head2 = new NODE();
    input(head2);

    head3 = new NODE();
    head3->next = NULL;
    multiplication(head1, head2, head3);

    output(head3);
    return 0;
}
#include <map>
void multiplication(NODE *h1, NODE *h2, NODE *h3)
{
    NODE *p1 = h1->next;
    NODE *p2 = h2->next;

    if (p1 == NULL || p2 == NULL)
    {
        h3->next = new NODE();
        h3->next->coef = 0;
        h3->next->exp = 0;
        h3->next->next = NULL;
        return;
    }

    std::map<int, int> ans;
    while (p1 != NULL)
    {
        p2 = h2->next;
        while (p2 != NULL)
        {
            int coef = p1->coef * p2->coef;
            int exp = p1->exp + p2->exp;
            ans[exp] += coef;
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    NODE *rev = new NODE();
    rev->next = NULL;
    for (auto it : ans)
    {
        if (it.second)
        {
            NODE *next = new NODE();
            next->coef = it.second;
            next->exp = it.first;
            next->next = rev->next;
            rev->next = next;
        }
    }

    NODE *prev = NULL;
    NODE *curr = rev->next;
    while (curr != NULL)
    {
        NODE *nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    h3->next = prev;
    if (h3->next == NULL)
    {
        h3->next = new NODE();
        h3->next->coef = 0;
        h3->next->exp = 0;
        h3->next->next = NULL;
    }
}