#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> t(m), w(m);
    for(int i = 0; i < m; i++)
    {
        cin >> t[i] >> w[i];
    }

    vector<long long> dp(n + 1, 0);

    for(int j = 0; j < m; j++)
    {
        long long score = 1LL * t[j] * w[j];
        for(int i = n; i >= t[j]; i--)
            dp[i] = max(dp[i], dp[i - t[j]] + score);
    }

    cout << dp[n] << endl;

    return 0;
}