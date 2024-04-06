#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 2e5 + 5;

int n, c;
int a[N];

int main()
{
    scanf("%d%d", &n, &c);
    For(i, 1, n)
        scanf("%d", a + i);
    sort(a + 1, a + n + 1);
    /*for (int i = 1; i <= n; i++)
        cout << i << " ";
    puts("");
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    cout << endl;*/
    // int r1 = 1, r2 = 1;
    long long ans = 0;
    /*for(int i = 1; i <= n; i++)
    {
        int k = a[i] + c;
        while(r1 <= n && a[r1] < k) r1++;
        while(r2 <= n && a[r2] <= k) r2++;
        if(a[r1] == k && a[r2 - 1] == k)
            ans += r2 - r1;
    }*/
    int l1 = 1, l2 = 1;
    for(int i = 1; i <= n; i++)
    {
        int k = a[i] - c;
        while(l1 <= n && a[l1] < k) l1++;
        while(l2 <= n && a[l2] <= k) l2++;
        if(a[l1] == k && l2 >= 2 && a[l2 - 1] == k)
            ans += l2 - l1; 
    }
    printf("%lld\n", ans);
    return 0;
}
