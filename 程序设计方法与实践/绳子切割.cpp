#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int ans = 0;
    cin >> n;
    vector<int> l(n);
    int max_len = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> l[i];
        max_len = max(max_len, l[i]);
    }

    int k;
    cin >> k;

    int low = 0;
    int high = max_len;
    
    auto check = [&](int len)
    {
        if(len == 0)
        {
            return true;
        }
        int count = 0;
        for(int x : l)
        {
            count += x/len;
        }
        return count >= k;
    };

    while(low <= high)
    {
        int mid = (low + high)/2;
        if(check(mid))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid -1;
        }
    }

    cout << ans << endl;

    return 0;
}