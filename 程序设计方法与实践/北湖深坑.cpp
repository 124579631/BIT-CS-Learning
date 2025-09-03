#include <iostream>

using namespace std;

int main()
{
    int t = 0;
    int n =0;
    cin >> t;
    while(t--)
    {
        cin >> n;
        long long *a = new long long [n];
        for(int i = 0; i< n; i++)
        {
            cin >> a[i];
        }
        int left = 0;
        int right = n-1;
        long long l_max = 0, r_max = 0, ans = 0;
        while(left < right)
        {
            if(a[left] <= a[right])
            {
                if(a[left] >= l_max)
                    l_max = a[left]; 
                else
                    ans += l_max - a[left];
                
                left++;
            }
            else
            {
                if(a[right] >= r_max)
                    r_max = a[right];
                else
                    ans += r_max - a[right];

                right--;
            }
        }

        cout << ans << endl;
        delete [] a;

    }

    return 0;
}