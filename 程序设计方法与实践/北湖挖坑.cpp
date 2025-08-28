#include <iostream>

using namespace std;

int main()
{
    int n = 0;
    long long h = 0;
    long long day = 0;
    cin >> n >> h;
    long long h_cur = 0;
    long long h_pre = h;
    for(int i = 0; i < n; i++)
    {
        cin >> h_cur;
        if(h - h_cur > h - h_pre)
            day += (h - h_cur) - (h - h_pre);

        h_pre = h_cur;
    }

    cout << day << endl;

    return 0;
}

/*
#include <iostream>
using namespace std;

int main() {
    int n;
    long long h;
    cin >> n >> h;

    long long ans = 0;
    long long prev_d = 0;   // 上一个位置的 d 值
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        long long d = h - a;   // 当前需要挖的深度
        if (d > prev_d) ans += d - prev_d;
        prev_d = d;
    }

    cout << ans << "\n";
    return 0;
}
*/