#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    vector<array<int, 4>> words(m);
    
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cin >> words[i][j];
        }
    }

    array<int, 4> start, end;
    for(int i = 0; i < 4; i++)
        cin >> start[i];    
    for(int i = 0; i < 4; i++)
        cin >> end[i];

    int s = -1, e = -1;//开始和结束的成语的索引
    for(int i = 0; i < m; i++)
    {
        if(words[i] == start)
            s = i;        
        if(words[i] == end)
            e = i;
    }

    unordered_map<int, vector<int>> head;
    for(int i = 0; i < m; i++)
    {
        head[words[i][0]].push_back(i);
    }

    vector<bool> visited(m, false);
    queue<pair<int, int>> queue;

    visited[s] = true;
    queue.push({s, 1});

    while(!queue.empty())
    {
        pair<int, int> temp = queue.front();
        int sta = temp.first;
        int step = temp.second;
        queue.pop();

        if(sta == e)
        {
            cout << step << endl;
            return 0;
        }

        int last = words[sta][3];
        for(int v : head[last])
        {
            if(!visited[v])
            {
                queue.push({v, step+1});
                visited[v] = true;
            }
        }
    }

    cout << -1 << endl;

    return 0;
}