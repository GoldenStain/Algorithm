#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100005;

struct mytype{
    int v, cnt;
    bool operator < (const mytype &tmp) const
    {
        return v < tmp.v;
    }
} a[N], tmp[N];

inline int read()
{
    int x = 0; char ch = getchar();
    while(ch < '0' || ch > '9')
        ch = getchar();
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

int n;

void mergesort(int l, int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    mergesort(l, mid); 
    mergesort(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while(i <= mid && j <= r)
    {
        if(a[i].v <= a[j].v) 
        {
            a[i].cnt += j - mid - 1;
            tmp[k++] = a[i++];
        }
        else 
        {
            a[j].cnt += mid - i + 1;
            tmp[k++] = a[j++];
        }
    }
    while(i <= mid)
    {
        a[i].cnt += r - mid;
        tmp[k++] = a[i++];
    }
    while(j <= r) tmp[k++] = a[j++];
    for(int t = l; t <= r; t++)
        a[t] = tmp[t];
}

int main()
{
    n = read();
    for(int i = 1; i <= n; i++)
    {
        a[i].v = read();
    }
    mergesort(1, n);
    long long ans = 0;
    for(int i = 1; i <= n; i++)
        ans += (long long) a[i].cnt * (a[i].cnt + 1) / 2;
    cout << ans << endl;
    system("pause");
    return 0;
}