#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(char data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* buildTree(char* In, char* Post, int len)
{
    if(len <= 0) return NULL;
    
    char rootVal = Post[len - 1];
    Node* root = createNode(rootVal);
    int k = 0;
    while(k < len)
    {
        if(In[k] == rootVal)
            break;
        k++;
    }

    root->left = buildTree(In, Post, k);
    root->right = buildTree(In + k + 1, Post + k, len - k - 1);

    return root;
}

void levelOrder(Node* root)
{
    if(root == NULL) return;
    
    Node* queue[1000];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;
    
    while(front < rear)
    {
        Node* current = queue[front++];
        printf("%c", current->data);

        if(current->left != NULL)
            queue[rear++] = current->left;
        if(current->right != NULL)
            queue[rear++] = current->right;
    }
    printf("\n");

}

int main()
{
    char InOrder[1000];
    char PostOrder[1000];

    while(scanf("%s", InOrder) != EOF && scanf("%s", PostOrder) != EOF)
    {
        int len = strlen(InOrder);

        Node* root = buildTree(InOrder, PostOrder, len);

        levelOrder(root);
    }

    return 0;
}