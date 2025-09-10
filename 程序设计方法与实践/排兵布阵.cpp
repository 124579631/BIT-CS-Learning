#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector <long long> x(n), y(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }

    sort(y.begin(), y.end());
    long long y_sum = 0;
    for(int i = 0; i < n; i++)
    {
        y_sum += abs(y[i] - y[n/2]);
    }

    sort(x.begin(), x.end());
    vector <long long> z(n);
    for(int i = 0; i < n; i++)
    {
        z[i] = x[i] - i;
    }
    sort(z.begin(), z.end());
    long long x_sum = 0;
    for(int i = 0; i < n; i++)
    {
        x_sum += abs(z[i] - z[n/2]);
    }

    cout << x_sum + y_sum << endl;

    return 0;
}