#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 +5;

int n;
int a[N], b[N];
unordered_map<int, int> F;

int main()
{
    int ans = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    for(int i = 1; i <= n; i++)
        F[b[i]] = i;
    for(int i = 1; i <= n; i++)
        while(a[i] != b[i])
        {
            swap(a[i], a[F[a[i]]]);
            ans++;
        }
    cout << ans << endl;
    return 0;
}
