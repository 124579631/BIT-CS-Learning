#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector <pair<int, int>> tasks(n);
    for(int i  = 0; i < n; i++)
    {
        cin >> tasks[i].second >> tasks[i].first;
    }
    sort(tasks.begin(), tasks.end());//按结束时间排序

    int count = 1;
    int end = tasks[0].first;
    for(int i  = 1; i < n; i++)
    {
        if(tasks[i].second >= end)
        {
            count++;
            end = tasks[i].first;
        }
    }
    cout << count << endl;
    return 0;
}