#include <iostream>
#include <string>

 using namespace std;

string add(string a, string b);

 int main()
 {
    int t = 0;
    cin >> t;
    while(t--)
    {
        string a, b, c;
        cin >> a >> b;
        c = add(a,b);
        cout << c;
    }

 }

string add(string a, string b)
{
    int i = a.size() - 1, j = b.size() - 1, k = 0, pre = 0;
    string ans;
    while(i >= 0 || j >=0)
    {
        int sum = pre;
        if(i >= 0)
        {
            sum += a[i] - '0';
            i--;
        }
        if(j >= 0)
        {
            sum += b[j] - '0';
            j--;
        }
        ans[k] = sum%2 + '0';
        k++;
        pre = sum/2;
    }
    return ans;
}