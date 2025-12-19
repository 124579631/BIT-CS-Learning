#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_WEIGHT 32827

typedef struct
{
    char u, v;
    int w;
} Edge;

int graph[100][100];
int dist[100];
int visited[100];
char nodes[100];
int node_count = 0;

int get_index(char c)
{
    for(int i = 0; i < node_count; i++)
    {
        if(nodes[i] == c)
            return i;
    }

    return -1;
}

void add_node(char c)
{
    if(get_index(c) == -1)
        nodes[node_count++] = c;
}

int cmp(const void* a, const void* b)
{
    return (*(char*)a - *(char*)b);
}

void dijkstra(int start, int n)
{
    for(int i = 0; i < n; i++)
    {
        dist[i] = MAX_WEIGHT;
        visited[i] = 0;
    }
    dist[start] = 0;

    for(int i = 0; i < n; i++)
    {
        int u = -1;
        int min_dist = MAX_WEIGHT;

        for(int j = 0; j < n; j++)
        {
            if(!visited[j] && dist[j] < min_dist)
            {
                min_dist = dist[j];
                u = j;
            }
        }
        visited[u] = 1;

        if(u == -1) break;

        for(int v = 0; v < n; v++)
        {
            if(!visited[v] && graph[u][v] != MAX_WEIGHT)
            {
                if(dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

}

int main()
{
    int n, e;
    char start;
    Edge edges[MAX_N * MAX_N];

    if(scanf("%d,%d,%c", &n, &e, &start) != 3)
        return 0;

    add_node(start);

    for(int i = 0; i < e; i++)
    {
        scanf(" <%c,%c,%d>", &edges[i].u, &edges[i].v, &edges[i].w);
        add_node(edges[i].u);
        add_node(edges[i].v);
    }

    qsort(nodes, n, sizeof(char),cmp);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            graph[i][j] = (i == j) ? 0 : MAX_WEIGHT;
    }

    for(int i = 0; i < e; i++)
    {
        int u = get_index(edges[i].u);
        int v = get_index(edges[i].v);

        if(edges[i].w < graph[u][v])
            graph[u][v] = edges[i].w;
    }

    int start_id = get_index(start);
    dijkstra(start_id, n);

    for(int i = 0; i < n; i++)
    {
        printf("%c:%d\n", nodes[i], dist[i]);
    }

    return 0;
}