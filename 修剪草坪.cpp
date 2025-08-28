#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

#define MAX 101

int main()
{
    int max = 0;
    int n,m;
    int lawn[MAX][MAX] = {0};
    int row_max[MAX];
    int col_max[MAX];
    bool ans = true;

    cin >> n >> m;
    for(int i = 0; i < n; i++)//读取目标草坪高度
    {
        for(int j = 0; j < m; j++)
        {
            cin >> lawn[i][j];
        }
    }

    for(int i = 0; i < n; i++)
    {
        row_max[i] = lawn[i][0];
        for(int j = 1; j < m; j++)
        {
            if(lawn[i][j] > row_max[i])
                row_max[i] = lawn[i][j];
        }
    }

    for(int j = 0; j < m; j++)
    {
        col_max[j] = lawn[0][j];
        for(int i = 1; i < n; i++)
        {
            if(lawn[i][j] > col_max[j])
                col_max[j] = lawn[i][j];
        }
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(lawn[i][j] < row_max[i] && lawn[i][j] < col_max[j])
            {   cout << "NO" << endl;
                return 0;
            }
        }
    }

    cout << "YES" << endl;

    return 0;
}