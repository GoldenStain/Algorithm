#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5;

int n, arr[3][N], base[N];
long long ans;

int findless(int a[], int x) //返回最大的小于x的数的下标
{
    int l = 0, r = n + 1;
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(a[mid] < x) l = mid;
        else r = mid - 1;
    }
    return l;
}

int findgreater(int a[], int x) // 返回最小的大于x的数的下标
{
    int l = 0, r = n + 1;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(a[mid] > x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < 3; i++)
    {
        arr[i][n + 1] = N;
        for(int j = 1; j <= n; j++)
            scanf("%d", &arr[i][j]);
    }
    for(int i = 0; i < 3; i++)
        sort(arr[i] + 1, arr[i] + n + 1);
    for(int i = 1; i <= n; i++)
    {
        base[i] = findless(arr[0], arr[1][i]);
    }
    for(int i = 1; i <= n; i++)
    {
        ans += (long long)base[i] * (n - findgreater(arr[2], arr[1][i]) + 1);
    }
    printf("%lld\n", ans);
    return 0;
}
