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

typedef struct
{
    int data[1000];
    int front;
    int rear;
} Queue;

void InitQueue(Queue *q)
{
    q->front = q->rear = 0;
}

void EnQueue(Queue *q, int e)
{
    if((q->rear + 1) % 1000 == q->front) return;

    q->data[q->rear] = e;
    q->rear = (q->rear + 1) % 1000;
}

void DeQueue(Queue *q, int *e)
{
    if(q->front == q->rear) return;
    
    *e = q->data[q->front];
    q->front = (q->front + 1) % 1000;
}

int QueueEmpty(Queue q)
{
    return q.front == q.rear;
}

void CreateGraph(ALGraph *G)
{
    int i = 0;
    char ch;

    while(scanf(" %c", &ch) && ch != '*')
    {
        G->VerticesList[i].data = ch;
        G->VerticesList[i].adj = NULL;
        i++;
    }
    G->numVertices = i;
    G->numEdges = 0;

    int u, v;
    while(scanf("%d,%d", &u, &v) == 2 && (u != -1 && v != -1))
    {
        EdgeNode *p1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        p1->dest = v;
        p1->next = G->VerticesList[u].adj;
        G->VerticesList[u].adj = p1;

        EdgeNode *p2 = (EdgeNode*)malloc(sizeof(EdgeNode));
        p2->dest = u;
        p2->next = G->VerticesList[v].adj;
        G->VerticesList[v].adj = p2;

        G->numEdges++;
    }
}

void PrintGraph(ALGraph G)
{
    printf("the ALGraph is\n");
    for(int i = 0; i < G.numVertices; i++)
    {
        printf("%c", G.VerticesList[i].data);
        EdgeNode *p = G.VerticesList[i].adj;
        while(p)
        {
            printf(" %d", p->dest);
            p = p->next;
        }
        printf("\n");
    }
}

void BFS(ALGraph G)
{
    printf("the Breadth-First-Seacrh list:");

    int visited[1000] = {0};
    Queue Q;
    InitQueue(&Q);

    for(int i = 0; i < G.numVertices; i++)
    {
        if(!visited[i])
        {
            visited[i] = 1;
            printf("%c", G.VerticesList[i].data);
            EnQueue(&Q, i);

            while(!QueueEmpty(Q))
            {
                int u;
                DeQueue(&Q, &u);

                EdgeNode *p = G.VerticesList[u].adj;
                while(p)
                {
                    int w = p->dest;
                    if(!visited[w])
                    {
                        printf("%c", G.VerticesList[w].data);
                        visited[w] = 1;
                        EnQueue(&Q, w);
                    }
                    p = p->next;
                }
            }
        }
    }
    printf("\n");
}

int main()
{
    ALGraph Graph;
    CreateGraph(&Graph);
    PrintGraph(Graph);
    BFS(Graph);

    return 0;
}