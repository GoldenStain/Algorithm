#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 10005;

int n, a[N];

int main()
{
    int ans = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++)
        while(a[i] != i)
        {
            ans++;
            swap(a[i], a[a[i]]);
        }
    cout << ans << endl;
    return 0;
}