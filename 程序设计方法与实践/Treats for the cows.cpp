#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> tr(n+1);
    for(int i = 1; i <= n; i++)
        cin >> tr[i];

    vector<vector<int>> dp(n+2, vector<int>(n+2, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int l = 1; l <= n - i + 1; l++)
        {
            int r = i - 1 + l;
            int age = n - r + l;
            dp[l][r] = max(tr[l] * age + dp[l+1][r], tr[r] * age + dp [l][r-1]);
        }
    }

    cout << dp[1][n] << endl;

    return 0;
}