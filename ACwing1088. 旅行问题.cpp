#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 2e6 + 5;

int n, hh, tt;  //check
ll p[N], d[N], q[N], s[N];
bool flag[N];

int main()
{
    scanf("%d", n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &p[i], &d[i]);
        s[i] = p[i] - d[i];
        s[i + n] = s[i];
    }
    for(int i = 1; i <= 2 * n; i++) s[i] += s[i - 1];
    //长度为n的滑动窗口
    for(int i = 2 * n - 1; i; i--)
    {
        if(hh <= tt && q[tt] > i + n - 1) hh++;
        while(hh <= tt && )
    }
    return 0;
}