#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define R(x) x = read()
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
       x = x * 10 + ch - '0';
       ch = getchar();
    }
     return x * f;
}

const int N = 5e4 + 5, M = 1e5 + 5;
typedef long long LL;

int n, a[N];
LL ans;
int cnt[M<<1]; //桶
int Min[N], Max[N];

void solve(int l, int r) // 当前处理l~r
{
    if(l == r)
    {
        ans++;
        return;
    }
    int mid = (l + r) >> 1;

    // 处理l,r横跨两边的
    Min[mid] = Max[mid] = a[mid];
    // i <= mid, Min,Max表示后缀最值
    for(int i = mid - 1; i >= l; i--)
    {
        Min[i] = min(a[i], Min[i + 1]);
        Max[i] = max(a[i], Max[i + 1]);
    }
    Min[mid + 1] = Max[mid + 1] = a[mid + 1];
    // i > mid, Min,Max表示前缀最值
    for(int i = mid + 2; i <= r; i++)
    {
        Min[i] = min(a[i], Min[i - 1]);
        Max[i] = max(a[i], Max[i - 1]);
    }
    // ----------------最大值在左边
    int Pr1 = mid + 1, Pr2 = mid + 1;
    for(int Pl = mid; Pl >= l; Pl--)
    {
        // 最大值在左边，最小值在右边
        while(Pr1 <= r && Max[Pr1] < Max[Pl]) cnt[Min[Pr1] + Pr1 + M]++, Pr1++; //注意这里可以取等号
        while(Pr2 < Pr1 && Min[Pr2] > Min[Pl]) cnt[Min[Pr2] + Pr2 + M]--, Pr2++;// 这里不能取等号
        // 最后有解的区间是 [Pr2, Pr1 - 1]
        ans += cnt[Max[Pl] + Pl + M];
        // 判断最值均在左边的情况是否成立
        int TmpR = Max[Pl] - Min[Pl] + Pl;
        if(TmpR > mid && TmpR < Pr2) ans++; 
    }
    // ----------------最大值在左边
    for(int i = Pr2; i < Pr1; i++)
        cnt[Min[i] + i + M] = 0; // 清空影响
    // ----------------最大值在右边
    int Pl1 = mid, Pl2 = mid;
    for(int Pr = mid + 1; Pr <= r; Pr++)
    {
        // 最大值在右边，最小值在左边
        while(Pl1 >= l && Max[Pl1] < Max[Pr]) cnt[Min[Pl1] - Pl1 + M]++, Pl1--;
        while(Pl2 > Pl1 && Min[Pl2] > Min[Pr]) cnt[Min[Pl2] - Pl2 + M]--, Pl2--;
        ans += cnt[Max[Pr] - Pr + M];
        // 判断最值均在右边的情况是否成立
        int TmpL = Min[Pr] - Max[Pr] + Pr;
        if(TmpL <= mid && TmpL > Pl2) ans++;
    }
    // ----------------最大值在右边
    for(int i = Pl2; i > Pl1; i--)
        cnt[Min[i] - i + M] = 0; // 清空影响
    solve(l, mid);solve(mid + 1, r);
}

int main()
{
    R(n);
    For(i, 1, n)
        R(a[i]);
    solve(1, n);
    printf("%lld\n", ans);
    return 0;
}
