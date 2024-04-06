#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5, M = 1e6 + 5;

int n, x;
int fa[M];

void init()
{
    for(int i = 1; i <= M; i++)
        fa[i] = i;
}

int find(int x)
{
    if(x == fa[x])
        return x;
    return fa[x] = find(fa[x]);
}

int main()
{
    scanf("%d", &n);
    init();
    For(i,1,n)
    {
        scanf("%d", &x);
        int a = find(x);
        if(a != x)
        {
            printf("%d ", a);
            fa[a] = a + 1;
        }
        else
        {
            printf("%d ", x);
            fa[x] = x + 1;
        }
    }
    return 0;
}
