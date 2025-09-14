#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct node
{
    int x;
    int y;
    int t;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    while(t--)
    {
        int n, m, k;
        cin >> n >> m >> k;
        vector<string> map(n);
        for(int i = 0; i < n; i++)
        {
            cin >> map[i];
        }

        int sx, sy;
        int ex, ey;
        for(int i = 0; i < n; i++)//S、E位置
        {
            for(int j = 0; j < m; j++)
            {
                if(map[i][j] == 'S')
                {
                    sx = i;
                    sy = j;
                }
                if(map[i][j] == 'E')
                {
                    ex = i;
                    ey = j;
                }
            }
        }

        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(k, false)));
        queue<node> posi;
        posi.push({sx, sy, 0});
        visited[sx][sy][0] = true;

        int ans = -1;
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        while(!posi.empty())
        {
            node cur = posi.front();
            posi.pop();

            int x = cur.x, y = cur.y, t = cur.t;

            if(x == ex && y == ey)
            {
                ans = t;
                break;
            }

            for(int d = 0; d < 4; d++)
            {
                int nx = x + dx[d], ny = y + dy[d], nt = t + 1;
                if(nx < 0 || nx >= n || ny < 0 || ny >= m)
                    continue;
                char c = map[nx][ny];
                if(c == '#')
                {
                    continue;
                }
                else if(c == '*')
                {
                    if(nt % k != 0)
                        continue;
                }
                if(!visited[nx][ny][nt%k])
                {
                    posi.push({nx, ny, nt});
                    visited[nx][ny][nt%k] = true;
                }
            }
        }

        cout << ans << endl;

    }

    return 0;
}