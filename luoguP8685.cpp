#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5;

inline int read()
{
    int x = 0; char ch=getchar();
    while(ch<'0'||ch>'9')
        ch = getchar();
    while(ch>='0'&&ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x;
}

int n, m, t, cnt;
vector<int> _orders[N];

void check(bool &f, int l)
{
    if(!f && l > 5)
        f = true;
    if(f && l <= 3)
        f = false;
}

void calculate_priority(vector<int> &tar, int id)
{
    int last_time = 0, _level = 0;
    bool in_cache = false;
    for(int _time:tar)
    {
        _level = max(0, _level - max(0, _time - last_time - 1));
        check(in_cache, _level);
        _level += 2;
        check(in_cache, _level);
        last_time = _time;
    }
    _level = max(0, _level - (t - last_time));
    check(in_cache, _level);
    if(in_cache)
        cnt++;
}

int main()
{
    n=read();m=read();t=read();
    For(i,1,m)
    {
        int ts = read(), id = read();
        _orders[id].push_back(ts);
    }
    For(i,1,n)
    {
        if(!_orders[i].empty())
        {
            sort(_orders[i].begin(), _orders[i].end());
            calculate_priority(_orders[i], i);
        }
    }
    printf("%d\n", cnt);
    return 0;
}
