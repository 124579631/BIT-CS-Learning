#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> left(100000);
    vector<int> right(100000);
    int balance = 0;
    int max_count = 0;

    for(int i = 0; i < n; i++)
    {
        int count = 0;
        int min_count = 0;//是否出现过需要左括号的情况
        string s;
        cin >> s;
        for(char c : s)
        {
            if(c == '(')
                count++;
            else
                count--;
            min_count = min(count, min_count);
        }

        if(min_count >= 0)//左括号或平衡
        {
            if(count == 0)
                balance++;
            else
            {
                left[count]++;
                max_count = max(count, max_count);
            }
        }
        else
        {
            if(count < 0 && min_count ==count)
            {
                right[-count]++;
                max_count = max(-count, max_count);
            }
        }
    }

    long long ans = balance/2;
    for(int i = 0; i <= max_count; i++)
    {
        ans += min(left[i], right[i]);
    }

    cout << ans << endl;

    return 0;
}