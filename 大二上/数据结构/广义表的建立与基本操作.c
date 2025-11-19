#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    int tag;
    union
    {
        char atom;
        struct
        {
            struct node *hlink;
            struct node *tlink;
        } ptr;
    };
} GNode, *GList;

int FindFirstComma(char *s, int start, int end)
{
    int i = start;
    int count = 0;
    while(i < end)
    {
        if(s[i] == '(') count++;
        else if(s[i] == ')') count --;
        else if(s[i] == ',' && count == 0) return i;
        i++;
    }
    return -1;
}

int CreateGList( GList *L, char *S )
{
    int len = strlen(S);

    if(len == 0 || (len == 1 && S[0] == '\0'))
    {
        *L = NULL;
        return 1;
    }

    if(len == 1 && isalpha(S[0]))
    {
        *L = (GList)malloc(sizeof(GNode));
        if(!(*L))   exit(1);
        (*L)->tag = 0;
        (*L)->atom = S[0];
        return 1;
    }

    if(S[0] == '(' && S[len - 1] == ')')
    {
        *L = (GList)malloc(sizeof(GNode));
        if(!(*L))   exit(1);
        (*L)->tag = 1;
        (*L)->ptr.hlink = NULL;
        (*L)->ptr.tlink = NULL;

        char *sub = (char *)malloc(len - 1);
        strncpy(sub, S + 1, len - 2);
        sub[len - 2] = '\0';
        int sub_len = len - 2;
        
        if(sub_len == 0)
        {
            free(sub);
            return 1;
        }

        int commaPos = FindFirstComma(sub, 0, sub_len);
        if(commaPos == -1)
        {
            char *headStr = (char *)malloc(sub_len + 1);
            strcpy(headStr, sub);
            CreateGList(&((*L)->ptr.hlink), headStr);
            (*L)->ptr.tlink = NULL;
            free(headStr);
        }
        else
        {
            char *headStr = (char *)malloc(sub_len + 1);
            strncpy(headStr, sub, commaPos);
            headStr[commaPos] = '\0';

            CreateGList(&((*L)->ptr.hlink), headStr);
            free(headStr);

            char *tailStr = (char *)malloc(sub_len - commaPos + 2);
            tailStr[0] = '(';
            strncpy(tailStr +  1, sub + commaPos + 1, sub_len - commaPos -1);
            tailStr[sub_len - commaPos] = ')';
            tailStr[sub_len - commaPos + 1] = '\0';

            CreateGList(&((*L)->ptr.tlink), tailStr);
            free(tailStr);
        }

        free(sub);
        return 1;
    }
    return 0;
}

GList GetHead( GList L)
{
    if(!L || L->tag == 0 || L->ptr.hlink == NULL)   return NULL;
    return L->ptr.hlink;
}

GList GetTail( GList L)
{
    if(!L || L->tag == 0 || L->ptr.tlink == NULL)    return NULL;
    return L->ptr.tlink;
}

void DestroyGList(GList *L)
{
    if (*L == NULL) return;

    if ((*L)->tag == 1)
    {
        DestroyGList(&((*L)->ptr.hlink));
        DestroyGList(&((*L)->ptr.tlink));
    }
    
    free(*L);
    *L = NULL;
}

void DestroyHead( GList *L)
{
    if(*L == NULL || (*L)->tag == 0) return;

    DestroyGList(&((*L)->ptr.hlink));
    printf("free head node\n");
    free(*L);
    *L = NULL;
}

void DestroyTail(GList *L)
{
    if (*L == NULL || (*L)->tag == 0) return;

    printf("destroy tail\n");
    DestroyGList(&((*L)->ptr.tlink));
    
    free(*L);
    *L = NULL;
}

void PrintGList( GList L)
{
    if(L == NULL)
    {
        printf("()");
        return;
    }

    if(L->tag ==0)
        printf("%c", L->atom);
    else
    {
        printf("(");
        GList current = L;
        while(current != NULL && current->ptr.hlink != NULL)
        {
            PrintGList(current->ptr.hlink);
            current = current->ptr.tlink;
            if (current != NULL)
            {
                if (current->ptr.hlink != NULL)
                    printf(",");
            }
        }
        printf(")");
    }
}

int main()
{
    GList L = NULL;
    char s[1000];
    
    if(fgets(s, sizeof(s), stdin));
    s[strcspn(s, "\n")] = 0;

    if(CreateGList(&L, s) == 0) return 1;
    printf("generic list: ");
    PrintGList(L);
    printf("\n");

    int op;
    while(scanf("%d", &op) == 1)
    {
        if(L == NULL || L->tag == 0)    break;
        GList newL = NULL;
        if(op == 1)
        {
            newL = GetHead(L);
            DestroyTail(&L);
            printf("free list node\n");
            L = newL;
        }
        else if(op == 2)
        {
            newL = GetTail(L);
            DestroyHead(&L);
            printf("free list node\n");
            L = newL;
        }
        else
            break;

        printf("generic list: ");
        PrintGList(L);
        printf("\n");

        if (L == NULL || L->tag == 0)    break;
    }

    DestroyGList(&L);

    return 0;
}