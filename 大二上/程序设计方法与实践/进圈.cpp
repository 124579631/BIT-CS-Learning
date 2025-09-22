#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int INF = 1e9;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<string> map(n);
    for(int i = 0; i < n; i++)
        cin >> map[i];

    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    sx--; sy--; ex--; ey--;

    vector<vector<int>> dist(n, vector<int>(m, INF));
    queue<pair<int, int>> q;

    dist[sx][sy] = 0;
    q.push({sx, sy});

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        int cur = dist[x][y];

        for(int d = 0; d < 4; d++)
        {
            for(int step = 1; step <= k; step++)
            {
                int nx = x + dx[d] * step;
                int ny = y + dy[d] * step;

                if(nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if(map[nx][ny] == '#')
                    break;

                if(dist[nx][ny] < cur + 1)
                    break;
                if(dist[nx][ny] == INF)
                {
                    dist[nx][ny] = cur +1;
                    q.push({nx, ny});
                }
            }
        }
    }

    int ans = dist[ex][ey];
    if(ans == INF)
        ans = -1;

    cout << ans << endl;

    return 0;
}