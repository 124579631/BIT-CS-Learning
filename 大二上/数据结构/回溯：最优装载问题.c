#include <stdio.h>

int c;
int n;
int weight[101];
int x[101];
int best_x[101];
int cur_weight = 0;
int best_weight = 0;
int remain_weight = 0;

void backtrack(int i)
{
    if(i == n)
    {
        if(cur_weight > best_weight)
        {
            best_weight = cur_weight;
            for(int j = 0; j < n; j++)
                best_x[j] = x[j];
        }
        return;
    }
    
    remain_weight -= weight[i];

    if(cur_weight + weight[i] <= c)
    {
        x[i] = 1;
        cur_weight += weight[i];
        backtrack(i + 1);
        cur_weight -= weight[i];
    }

    if(cur_weight + remain_weight > best_weight)
    {
        x[i] = 0;
        backtrack(i + 1);
    }

    remain_weight += weight[i];
}

int main()
{
    if(scanf("%d %d", &c, &n) != 2) return 0;
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &weight[i]);
        remain_weight += weight[i];
    }

    backtrack(0);
    printf("%d\n", best_weight);
    for(int i = 0; i < n; i++)
    {
        if(best_x[i]  == 1)
            printf("%d ", i + 1);
    }
    printf("\n");

    return 0;
}