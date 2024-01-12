#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1005;

char str[N], ctr[N];
int f[N][N];

int main()
{
    cin >> str;
    int len = strlen(str);
    for(int i = 0; i < len; i++)
        ctr[len - 1 - i] = str[i];
    for(int i = 0; i < len; i++)
        for(int j = 0; j < len; j++)
        {
            if(str[i] == ctr[j])
            {
                if(i < 1 || j < 1)
                    f[i][j] = 1;
                else
                    f[i][j] = f[i - 1][j - 1] + 1;
            }
            else
            {
                int a = (i < 1) ? 0 : f[i - 1][j],
                    b = (j < 1) ? 0 : f[i][j - 1];
                f[i][j] = max(a, b);
            }
        }
    cout << len - f[len - 1][len - 1];
    return 0;
}
