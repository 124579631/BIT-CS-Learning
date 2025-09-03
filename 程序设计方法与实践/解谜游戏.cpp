#include <iostream>
#include <string>
#include <climits>

using namespace std;

void change(int lights[][16], int i, int j, int n, int m);

int main()
{
    int lights[16][16];
    int n = 0, m = 0, ans = INT_MAX;
    cin >> n >> m;

    for(int i = 0; i < n; i++)//初始状态
    {
        for(int j = 0; j< m; j++)
        {
            char num;
            cin >> num;
            lights[i][j] = num -'0';
        }
    }

    for(int count = 0; count < (1 << m); count++)
    {
        int temp[16][16];
        int press[16][16] = {0};
        int times = 0;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j< m; j++)
            {
                temp[i][j] = lights[i][j];
            }
        }

        for(int j = 0; j < m; j++)//第一行
        {
            if(count & (1 << j))//count为1的位按灯
            {
                press[0][j] = 1;
                change(temp, 0, j, n, m);
            }
        }

        for(int i = 1; i < n; i++)//剩余行
        {
            for(int j = 0; j < m;j++)
            {
                if(temp[i-1][j] == 1)
                {
                    press[i][j] = 1;
                    change(temp, i, j, n, m);
                }
            }
        }

        bool last = true;
        for(int j = 0; j < m; j++)
        {
            if(temp[n-1][j] == 1)
            {
                last = false;
                break;
            }
        }

        if(!last)
            continue;
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(press[i][j] == 1)
                    times++;
            }
        }

        if(times < ans)
            ans = times;
    }
    cout << ans << endl;

    return 0;
}

void change(int lights[][16], int i, int j, int n, int m)
{
    lights[i][j] = abs(lights[i][j]-1);
    if(i != 0) 
        lights[i-1][j] = abs(lights[i-1][j]-1);
    if(i != n-1) 
        lights[i+1][j] = abs(lights[i+1][j]-1);
    if(j != 0) 
        lights[i][j-1] = abs(lights[i][j-1]-1);
    if(j != m-1) 
        lights[i][j+1] = abs(lights[i][j+1]-1);
}