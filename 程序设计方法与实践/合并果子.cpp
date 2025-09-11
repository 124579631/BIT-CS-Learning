#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> a;

    for(int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        a.push(num);
    }

    long long sum = 0;
    while(a.size() > 1)
    {
        int x, y;
        x = a.top();
        a.pop();
        y = a.top();
        a.pop();
        sum += x+y;
        a.push(x+y);
    }

    cout << sum << endl;

    return 0;
}