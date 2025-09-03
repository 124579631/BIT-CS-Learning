#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

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
        int size = c.size() + 2;
        cout << setw(size) << a << endl;
        cout << '+' <<setw(size - 1) << b << endl;
        for(int i = 0; i < size; i++)
        {
            cout << '-';
        }
        cout << endl << setw(size) << c << endl;
    }

 }

string add(string a, string b)
{
    int i = a.size() - 1, j = b.size() - 1, pre = 0;
    string ans;
    while(i >= 0 || j >=0 || pre)
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
        ans.push_back(sum%2 + '0');
        pre = sum/2;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}