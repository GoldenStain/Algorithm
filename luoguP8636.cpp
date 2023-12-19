#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;
typedef long long LL;

const int N = 105;

int n;
LL a[N];
LL gcd(LL x, LL y)
{
    if (y)
        return gcd(y, x % y);
    return x;
}

LL lcd(LL x, LL y)
{
    return x * y / gcd(x, y);
}

struct fraction
{
    LL father, son;
    bool operator>(const fraction &t) const
    {
        return son * t.father > t.son * father;
    }
    bool operator<(const fraction &t) const
    {
        return son * t.father < t.son * father;
    }
    fraction operator/(const fraction &t) const
    {
        fraction c;
        c.father = father / t.father;
        c.son = son / t.son;
        return c;
    }
    bool operator!=(const fraction &t) const
    {
        return (father != t.father || son != t.son);
    }
    bool operator==(const fraction &t) const
    {
        return !(father != t.father || son != t.son);
    }
} f[N];

ostream& operator<<(std::ostream& os, const fraction& p) {
    os << p.son << "/" << p.father;
    return os;
}

int cnt;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    fraction ans;
    ans.father = 1;
    ans.son = 1e12;
    fraction mans;
    for (int i = 1; i < n; i++)
    {
        if(a[i] == a[i + 1])
            continue;
        fraction t;
        t.son = a[i + 1];
        t.father = a[i];
        LL g = gcd(a[i], a[i + 1]);
        t.father /= g;
        t.son /= g;
        f[++cnt] = t;
    }
    sort(f + 1, f + cnt + 1);
    for(int i = 1; i < cnt; i++)
    {
        if(f[i] == f[i + 1])
            continue;
        fraction t = f[i + 1] / f[i];
        ans = min(ans, t);
    }
    cout << min(ans, f[1]);
    return 0;
}
