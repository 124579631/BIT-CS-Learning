#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> map(n);
    for(int i = 0; i < n; i++)
        cin >> map[i];

    auto get = [&](int x, int y)
    {
        return x * m + y;
    };

    pair<int, int> start({-1, -1}), end({-1, -1});
    vector<int> doors;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(map[i][j] == 'N')
            {
                start.first = i;
                start.second = j;
            }
            else if (map[i][j] == 'C')
            {
                end.first = i;
                end.second = j;
            }
            else if(map[i][j] == 'E')
            {
                doors.push_back(get(i, j));
            }
        }
    }

    if(start.first < 0 || start.second < 0 || end.first < 0 || end.second < 0)
    {
        cout << "Bad Eureka" << endl;
        return 0;
    }

    vector<int> dist(n*m, -1);
    deque<int> dq;
    dq.push_back(get(start.first, start.second));
    dist[get(start.first, start.second)] = 0;

    bool door_used = false;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while(!dq.empty())
    {
        int pos = dq.front();
        dq.pop_front();
        int x = pos / m;
        int y = pos % m;
        int t = dist[pos];

        if(x == end.first && y == end.second)
        {
            cout << t << endl;
            return 0;
        }

        if(!door_used && map[x][y] == 'E' && !doors.empty())
        {
            door_used = true;
            for(int d : doors)
            {
                if(dist[d] == -1)
                {
                    dist[d] = t;
                    dq.push_front(d);
                }
            }
        }

        for(int d = 0; d < 4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx < 0 || nx >= n || ny < 0 ||ny >= m)
                continue;
            else if(map[nx][ny] == 'M')
                continue;
            
            if(dist[get(nx, ny)] == -1)
            {
                dist[get(nx, ny)] = t + 1;
                dq.push_back(get(nx, ny));
            }
        }
    }

    cout << "Bad Eureka" << endl;

    return 0;
}