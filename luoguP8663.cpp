#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5, M = 1e3 + 5;

int arr[M][3], n, k;

int main()
{
    scanf("%d%d", &n, &k);
    int x, m;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        m = x % k;
        if(x > arr[m][0])
        {
            arr[m][2] = arr[m][1];
            arr[m][1] = arr[m][0];
            arr[m][0] = x;
        }
        else if(x > arr[m][1])
        {
            arr[m][2] = arr[m][1];
            arr[m][1] = x;
        }
        else if(x > arr[m][2])
            arr[m][2] = x;
    }
    int ans = 0;
    for(int l = 0; l <= k * 2; l += k)
    {
        for(int a = 0; a < k; a++)
        //这里枚举时保证了a<=b<=c，可以节省一些时间，但是要注意，这里必须是小于等于，如果是小于号的话，可能会错过答案
            for(int b = max(a, l - a - k + 1); l - a - b >= b; b++)//l-a-k+1的由来：l - a - b <= k - 1
            {
                int c = l - a - b;
                ans = max(ans, arr[a][0] + arr[b][a == b] + arr[c][(a == c) + (b == c)]);
            }       
    }
    printf("%d\n", ans);
    return 0;
}
