#include <iostream>
#include <vector>

#define MOD 10000000

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, v;
    cin >> n >> v;
    
    vector<int> p(n);
    for(int i = 0; i < n; i++)
        cin >> p[i];

    vector<int> dp(v, 0);
    dp[0] = 1;

    for(int x : p)
    {
        vector<int> n_dp(dp);
        for(int i = 0; i < v; i++)
        {
            int ni = (i + x) % v;
            n_dp[ni] = (n_dp[ni] + dp[i]) % MOD;
        }
        dp.swap(n_dp);
    }

    int ans = (dp[0] - 1) % MOD;
    cout << ans << endl;

    return 0;
}