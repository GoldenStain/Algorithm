#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 2e6 + 5;

int n, hh, tt; // check
ll p[N], d[N], q[N], s[N], rs[N];
bool flag[N >> 1];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &p[i], &d[i]);
        s[i] = p[i] - d[i];
        rs[i] = p[i] - d[i - 1];
        s[i + n] = s[i];
        rs[i + n] = rs[i];
    }
    rs[1] = rs[n + 1] = p[1] - d[n];
    for (int i = 1; i <= 2 * n; i++)
        s[i] += s[i - 1];
    for (int i = 2 * n; i; i--)
        rs[i] += rs[i + 1];
    // 长度为n的滑动窗口
    q[0] = 2 * n - 1;
    for (int i = 2 * n - 2; i; i--)
    {
        if (q[hh] > i + n - 1)
            hh++;
        while (hh <= tt && s[q[tt]] >= s[i])
            tt--;
        q[++tt] = i;
        if (i <= n && s[q[hh]] >= s[i - 1])
            flag[i] = 1;
    }
    hh = tt = 0;
    q[0] = 1;
    for (int i = 2; i <= 2 * n; i++)
    {
        if (q[hh] < i - n + 1)
            hh++;
        while (hh <= tt && rs[q[tt]] >= rs[i])
            tt--;
        q[++tt] = i;
        if (i >= n + 1 && rs[q[hh]] >= rs[i + 1])
            flag[i - n] = 1;
    }
    for (int i = 1; i <= n; i++)
        if (flag[i])
            puts("TAK");
        else
            puts("NIE");
    system("pause");
    return 0;
}