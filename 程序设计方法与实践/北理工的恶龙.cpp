#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp_pos(const pair<long long, long long> & x, const pair<long long, long long> &y)
{
    return x.first < y.first;
}
bool cmp_neg(const pair<long long, long long> & x, const pair<long long, long long> &y)
{
    long long ax = x.first, ay = x.second;
    long long bx = y.first, by = y.second;
    if(ax + ay != bx + by)
    {
        return ax + ay > bx + by;
    }
    return ax > bx;
}

int main()
{
    int n;
    cin >> n;
    vector <pair<long long, long long>> pos, neg;
    for(int i = 0; i < n; i++)
    {
        long long x, y;
        cin >> x >> y;
        if(y >= 0)
            pos.emplace_back(x, y);
        else
            neg.emplace_back(x, y);
    }
    sort(pos.begin(), pos.end(), cmp_pos);
    sort(neg.begin(), neg.end(), cmp_neg);

    long long A = 0, cost = 0;
    for(auto &a : pos)
    {
        long long x = a.first, y = a.second;
        if(A < x)
        {
            cost += x-A;
            A = x;
        }
        A += y;
    }

    for(auto &a : neg)
    {
        long long x = a.first, y = a.second;
        if(A < x)
        {
            cost += x-A;
            A = x;
        }
        A += y;
    }    

    cout << cost << endl;

    return 0;
}