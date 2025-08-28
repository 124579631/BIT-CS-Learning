#include <iostream>

using namespace std;

int main() {
    int t = 0;
    long long n = 0;
    int ans = 0;

    cin >> t;

    while(t-- > 0)
    {
        ans = 0;
        cin >> n;
        for(long long i = 1; i < n; i <<= 1)
        {
            ans++;
        }
        cout << ans << endl;
    }

    return 0;
}
