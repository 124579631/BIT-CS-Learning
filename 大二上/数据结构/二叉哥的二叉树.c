#include <stdio.h>
#include <math.h>

int check(long long k, long long n, long long m)
{
    long long cost = 0;
    long long current_layer_count = k;

    for(int i = 0; i <= m; i++)
    {
        cost += current_layer_count;
        if(cost > n) return 0;
        
        if(current_layer_count == 1)
        {
            cost += m - i;
            if(cost > n) return 0;
            break;
        }

        current_layer_count = (current_layer_count + 1) / 2;
    }

    return cost <= n;
}

int main()
{
    int T;
    if(scanf("%d", &T) != 1) return 0;

    while (T--)
    {
        long long n, m;
        if(scanf("%lld %lld", &n, &m) != 2) break;

        if(n == 0)
        {
            printf("0\n");
            continue;
        }

        long long left = 1, right = n;
        if(m < 27)
        {
            long long limit = (long long)1 << m;
            if(right > limit)
                right = limit;
        }

        long long ans = 0;
        if (!check(1, n, m))
        {
            printf("0\n");
            continue;
        }
        
        while(left <= right)
        {
            long long mid = left + (right - left) / 2;
            if(check(mid, n, m))
            {
                ans = mid;
                left = mid + 1;
            }
            else
                right = mid - 1;
        }

        printf("%lld\n", ans);
    }

    return 0;
}