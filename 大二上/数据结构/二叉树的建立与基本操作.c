#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild, *rchild;
} TreeNode, *BiTree;

BiTree CreateBiTree()
{
    char ch;
    scanf("%c", &ch);

    if(ch == '#')
    {
        return NULL;
    }
    else
    {
        BiTree T = (BiTree)malloc(sizeof(TreeNode));
        T->data = ch;
        T->lchild = CreateBiTree();
        T->rchild = CreateBiTree();
        return T;
    }
}

void PreOrder(BiTree T)
{
    if(T)
    {
        printf("%c", T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T)
{
    if(T)
    {
        InOrder(T->lchild);
        printf("%c", T->data);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T)
{
    if(T)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c", T->data);
    }
}

int CountLeaf(BiTree T)
{
    if(!T)  return 0;

    if(!T->lchild && !T->rchild) return 1;
    return CountLeaf(T->lchild) + CountLeaf(T->rchild);
}

void SwapTree(BiTree T)
{
    if(!T) return;

    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;

    SwapTree(T->lchild);
    SwapTree(T->rchild);
}

void PrintTree(BiTree T, int depth)
{
    if(!T) return;
    
    for(int i = 0; i < depth; i++)
        printf("    ");
    printf("%c\n", T->data);
    PrintTree(T->lchild, depth + 1);
    PrintTree(T->rchild, depth + 1);
}

int main()
{
    BiTree T = CreateBiTree();
    
    printf("BiTree\n");
    PrintTree(T, 0);

    printf("pre_sequence  : ");
    PreOrder(T);
    printf("\n");
    
    printf("in_sequence   : ");
    InOrder(T);
    printf("\n");
    
    printf("post_sequence : ");
    PostOrder(T);
    printf("\n");

    printf("Number of leaf: %d\n", CountLeaf(T));

    SwapTree(T);
    printf("BiTree swapped\n");

    PrintTree(T, 0);
    
    printf("pre_sequence  : ");
    PreOrder(T);
    printf("\n");
    
    printf("in_sequence   : ");
    InOrder(T);
    printf("\n");
    
    printf("post_sequence : ");
    PostOrder(T);
    printf("\n");
    
    return 0;
}