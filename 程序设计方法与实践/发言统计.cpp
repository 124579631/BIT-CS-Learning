#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n = 0, ans = 0,i = 0;
    string a[1000];
    cin >> n;
    while(n--)
    {
        cin >> a[i];
        if(a[i].size()>10)
        {
            int check = 0;
            for(int j = 0; j < i; j++)
            {
                if(a[i] == a[j])
                {
                    check++;
                    break;
                }
            }
            if(!check)
                ans++;
        }
        i++;
    }
    cout << ans << endl;
}