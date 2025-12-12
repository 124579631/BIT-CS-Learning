#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int N, M;
long long ans = 0;

struct
{
    int r;
    int c;
} queens[10];

bool col_occupied[10];
bool d1_occupied[20];
bool d2_occupied[20];

bool is_covered(int r, int c)
{
    for(int i = 0; i < M; i++)
    {
        int qr = queens[i].r;
        int qc = queens[i].c;
        if(qr == r || qc == c || abs(qr - r) == abs(qc - c))
            return true;
    }
    return false;
}

bool check()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            if(!is_covered(i, j))
                return false;
    }
    return true;
}

void DFS(int row, int count)
{
    if(count == M)
    {
        if(check())
            ans++;
        return;
    }

    if(row == N) return;

    for(int c = 0; c < N; c++)
    {
        if(!col_occupied[c] && !d1_occupied[row - c + N] && !d2_occupied[row + c])
        {
            col_occupied[c] = true;
            d1_occupied[row - c + N] = true;
            d2_occupied[row + c] = true;
            queens[count].r = row;
            queens[count].c = c;

            DFS(row + 1, count + 1);

            col_occupied[c] = false;
            d1_occupied[row - c + N] = false;
            d2_occupied[row + c] = false;
        }
    }

    if(N - row > M - count)
        DFS(row + 1, count);
}

int main()
{
    scanf("%d %d", &N, &M);
    DFS(0, 0);
    printf("%lld\n", ans);

    return 0;
}