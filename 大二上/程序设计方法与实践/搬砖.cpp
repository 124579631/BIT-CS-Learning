#include <iostream>
#include <vector>

using namespace std;

long long merge(vector <long long>& a, int left, int mid, int right, vector <long long>& temp);
long long mergesort(vector <long long>& a, int left, int right, vector <long long>& temp);

int main()
{
    int n = 0;
    cin >> n;
    vector <long long> a(n), temp(n);
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cout << mergesort(a, 0, n, temp) << endl;
}

long long merge(vector <long long>& a, int left, int mid, int right, vector <long long>& temp)
{
    long long count = 0;
    int i = left, j = mid, k = left;
    while(i < mid && j < right)
    {
        if(a[i] <= a[j])
        {
            temp[k] = a[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = a[j];
            k++;
            j++;
            count += mid - i;
        }
    }

    while(i < mid)
    {
        temp[k] = a[i];
        k++;
        i++;        
    }
    while(j < right)
    {
        temp[k] = a[j];
        k++;
        j++;
    }

    for(int p = left; p < right; p++)
    {
        a[p] = temp[p];
    }

    return count;
}

long long mergesort(vector <long long>& a, int left, int right, vector <long long>& temp)
{
    long long count = 0;
    if(left + 1 < right)
    {
        int mid = (left + right)/2;
        count += mergesort(a, left, mid , temp);
        count += mergesort(a, mid, right , temp);
        count += merge(a, left, mid, right, temp);
    }
    return count;
}