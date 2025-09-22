#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n1, n2;
    int id = 0;
    while(cin >> n1 >> n2)
    {
        if(n1 == 0 && n2 == 0)
            break;
        id++;
        
        vector<int> a(n1), b(n2);
        for(int i = 0; i < n1; i++)
            cin >> a[i];
        for(int i = 0; i < n2; i++)
            cin >> b[i];

        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

        for(int i = 1; i <= n1; i++)
        {
            for(int j = 1; j <= n2; j++)
            {
                if(a[i - 1] == b[j - 1])
                    dp[i][j] = dp[i - 1][j -1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        cout << "Twin Towers #" << id << endl;
        cout << "Number of Tiles : " << dp[n1][n2] << endl;
    }

    return 0;
}