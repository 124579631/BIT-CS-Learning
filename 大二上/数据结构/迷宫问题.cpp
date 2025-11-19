#include <iostream>
#include <vector>
using namespace std;

int n, m;
int maze[105][105];
bool visited[105][105];
vector<pair<int, int>> path;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool DFS(int x, int y)
{
    if (x == n && y == m)
    {
        path.push_back({x, y});
        return true;
    }

    visited[x][y] = true;
    path.push_back({x, y});

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && maze[nx][ny] == 0 && !visited[nx][ny])
            if (DFS(nx, ny)) 
                return true;
    }

    path.pop_back();
    return false;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> maze[i][j];

    if (maze[1][1] == 1 || maze[n][m] == 1)
    {
        cout << "There is no solution!" << endl;
        return 0;
    }

    if (DFS(1, 1))
    {
        for (int i = 0; i < path.size(); i++)
            cout << "<" << path[i].first << "," << path[i].second << "> ";

        cout << endl;
    }
    else
        cout << "There is no solution!" << endl;

    return 0;
}
