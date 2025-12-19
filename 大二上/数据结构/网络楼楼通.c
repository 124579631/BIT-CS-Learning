#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int u;
    int v;
    int cost;
} Edge;

Edge edges[3001];
int parent[1001];

void init_dsu(int n)
{
    for(int i = 1; i <= n; i++)
        parent[i] = i;
}

int find_root(int x)
{
    if(parent[x] == x) return x;
    return parent[x] = find_root(parent[x]);
}

int union_sets(int x, int y)
{
    int rootx = find_root(x);
    int rooty = find_root(y);

    if(rootx != rooty)
    {
        parent[rootx] = rooty;
        return 1;
    }

    return 0;
}

int cmp(const void* a, const void* b)
{
    Edge* A = (Edge*)a;
    Edge* B = (Edge*)b;
    return A->cost - B->cost;
}

int main()
{
    int N, M;
    if(scanf("%d %d", &N, &M) != 2) return 0;

    for(int i = 0; i < M; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost);

    qsort(edges, M, sizeof(Edge), cmp);
    init_dsu(N);
    int totalcost = 0;
    int numofedges = 0;

    for(int i = 0; i < M; i ++)
    {
        if(union_sets(edges[i].u, edges[i].v))
        {
            totalcost += edges[i].cost;
            numofedges++;
            if(numofedges == N - 1) break;
        }
    }

    if(numofedges == N - 1)
        printf("%d\n", totalcost);
    else
        printf("-1\n");

    return 0;
}