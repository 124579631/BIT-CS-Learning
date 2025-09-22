#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<pair <long long, long long>>house(n);//first->color
        vector<int> ans(n, 0);
        vector<int> count(1000001, 0);//颜色计数
        for(int i = 0; i < n; i++)
        {
            cin >> house[i].first;
        }
        for(int i = 0; i < n; i++)
        {
            cin >> house[i].second;
        }

        int count_color = 0;
        vector<pair <long long, long long>>stack;

        for(int i = 0; i < n; i++)//入栈
        {
            long long color = house[i].first;
            long long height = house[i].second;
            while(!stack.empty() && stack.back().second <= height)//弹出低的
            {
                count[stack.back().first]--;
                if(count[stack.back().first] == 0)
                    count_color--;
                stack.pop_back();
            }
            if(count[color] == 0)
            {   
                count_color++;
            }
            count[color]++;
            stack.emplace_back(color, height);
            ans[i] = count_color;
        }

        cout << ans[0];
        for(int i = 1; i < n; i++)
        {
            cout << " " << ans[i];
        }
        cout << endl;

        for (auto & h : stack)
        {
            count[h.first] = 0;
        }
    }

    return 0;
}