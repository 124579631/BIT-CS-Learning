#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, cx, cy;
    cin >> n >> m >> cx >> cy;

    bool forbi[21][21] = {false};
    forbi[cx][cy] = true;

    int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};//Pi位置
    int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};
    for(int i = 0; i < 8; i++)
    {
        int x = cx + dx[i];
        int y = cy + dy[i];
        if(x >=0 && x <= n && y >= 0 && y <= m)    
            forbi[x][y] = true;
    }
    long long dp[21][21] = {0};  
    dp[0][0] = 1;
    for(int x = 0; x <= n; x++)
    {
        for(int y = 0; y <= m; y++)
        {
            if(forbi[x][y])
            {
                dp[x][y] = 0;
                continue;
            }
            if(x)
                dp[x][y] += dp[x-1][y];
            if(y)
                dp[x][y] += dp[x][y-1];
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}