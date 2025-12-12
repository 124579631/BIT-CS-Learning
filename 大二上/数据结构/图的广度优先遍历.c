#include <stdio.h>
#include <stdlib.h>

typedef struct Enode
{
    int dest;
    int weight;
    struct Enode *next;
} EdgeNode;

typedef struct Vnode
{
    char data;
    EdgeNode *adj;
} VertexNode;

typedef struct
{
    VertexNode VerticesList[1000];
    int numVertices;
    int numEdges;
} ALGraph;



int main()
{

    return 0;
}