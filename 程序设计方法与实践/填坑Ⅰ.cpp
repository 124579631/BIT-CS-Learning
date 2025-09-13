#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    while(cin >> n)
    {
        vector<long long> a(n);
        long long max_h = 0;
        for(int i = 0; i < n; i++)
        {
            cin >> a[i];
            max_h = max(max_h, a[i]);
        }

        vector<int> b(n);//差值奇偶性
        for(int i = 0; i < n; i++)
        {
            b[i] = (max_h - a[i]) % 2;
        }

        vector<int> stack;
        for(int i = 0; i < n; i++)
        {
            if(!stack.empty() && stack.back() == b[i])
            {
                stack.pop_back();
            }
            else
            {
                stack.push_back(b[i]);
            }
        }

        if(stack.size() <=1)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }

    return 0;
}