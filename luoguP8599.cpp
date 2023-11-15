#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e6 + 5, M = 362880;
int n, a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int getnum(int s, int t)
{
    int res = 0;
    for(int i = t, x = 1; i >=s; i--, x *= 10)
    {
        res += a[i] * x;
    }
    return res;
}

int main()
{
    int ans = 0;
    scanf("%d", &n);
    int tmp, k;
    for(tmp = 1, k = 1;tmp <= n; tmp *= 10, k++);
    k--;
    for(int i = 1; i <= M; i++)
    {
        //设置断点
        for(int j = 1; j <= k; j++)
        {
            int now = getnum(1, j);
            if(now >= n) break; 
            // 再次设置断点
            int left = n - now;
            for(int j2 = j + 1; j2 < 9; j2++)
            {
                int now2 = getnum(j + 1, j2),
                    now3 = getnum(j2 + 1, 9);
                if(now2 % now3) continue;
                if(now2 / now3 == left) ans++;
            }
        }
        next_permutation(a + 1, a + 10);
    }
    cout << ans << endl;
    system("pause");
    return 0;
}