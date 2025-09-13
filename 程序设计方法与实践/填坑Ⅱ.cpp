#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main()
{
    int n;
    while(cin >> n)
    {
        vector<long long> a(n);
        vector<long long> stack;
        bool check = true;
        for(int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        long long max = *max_element(a.begin(), a.end());
        for(int i = 0; i < n; i++)
        {
            long long h = a[i]; 
            if(!stack.empty() && stack.back() == h)
            {
                stack.pop_back();
            }
            else if(!stack.empty() && stack.back() < h)
            {
                check = false;
                break;
            }
            else
            {
                stack.push_back(h);
            }
        }

        if(!check)
        {
            cout << "NO\n";
        }
        else
        {
            if(stack.empty())
                cout << "YES\n";
            else if(stack.size() == 1 && stack.back() == max)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }

    return 0;
}