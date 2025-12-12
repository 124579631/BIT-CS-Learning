#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TreeNode
{
    char data;
    int degree;
    struct TreeNode *firstchild;
    struct TreeNode *nextsibling;
} TreeNode, *Tree;

int degree_count[10000];
int max_degree = 0;
char *input_ptr;

Tree createList()
{
    if(*input_ptr == '\0' || *input_ptr != '(') return NULL;
    input_ptr++;
    if(*input_ptr == '\0' || *input_ptr == ')' || *input_ptr ==',') return NULL;

    Tree root = (Tree)malloc(sizeof(TreeNode));
    if(root == NULL) exit(0);

    root->data = *input_ptr;
    root->degree = 0;
    root->firstchild = NULL;
    root->nextsibling = NULL;
    input_ptr++;
    
    Tree currentchild = NULL;
    while(*input_ptr == ',')
    {
        input_ptr++;

        Tree childtree = createList();
        if(childtree == NULL)
            break;

        root->degree++;

        if(root->firstchild == NULL)
            root->firstchild = childtree;
        else
            currentchild->nextsibling = childtree;

        currentchild = childtree;
    }

    if(*input_ptr == '\0' || *input_ptr != ')') return NULL;
    input_ptr++;

    return root;
}

Tree createTree(char *input_str)
{
    input_ptr = input_str;
    return createList();
}

void printTree(Tree T, int level)
{
    if(T == NULL) return;

    for(int i = 0; i < level * 4; i++)
        printf(" ");

    printf("%c\n", T->data);

    printTree(T->firstchild, level + 1);
    printTree(T->nextsibling, level);
}

void countDegree(Tree T)
{
    if(T == NULL) return;

    degree_count[T->degree]++;
    if(T->degree > max_degree)
        max_degree = T->degree;
    countDegree(T->firstchild);
    countDegree(T->nextsibling);
}

int main()
{
    char input_str[1000];
    fgets(input_str, sizeof(input_str), stdin);

    input_str[strcspn(input_str, "\n")] = 0;
    Tree Root = createTree(input_str);

    printTree(Root, 0);

    memset(degree_count, 0, sizeof(degree_count));
    countDegree(Root);
    printf("Degree of tree: %d\n", max_degree);
    for(int i = 0; i <= max_degree; i++)
        printf("Number of nodes of degree %d: %d\n", i, degree_count[i]);

    return 0;
}