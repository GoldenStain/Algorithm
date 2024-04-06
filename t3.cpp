#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <string.h>
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1005;

char s[N], s2[N];
int f[N][N],n;


void solve()
{
    int lens=strlen(1+s);
    n=strlen(1+s);
	  for (int length = 2; length <= n; ++length) {  
        for (int i = 1; i <= n - length + 1; ++i) {
            int j = i + length - 1;
            if (s[i] == s[j]) {
                f[i][j] = f[i + 1][j - 1];
            } else {
                f[i][j] = min(f[i + 1][j], f[i][j - 1]) + 1;
            }
        }
    }
    cout << f[1][n] << endl;
}

string t1, t2;

void build()
{
    int i = 1, j = n;
    while (i < j) {
        cout << i << " " << j << endl;
        if (s[i] == s[j]) {
           // cout << "1" << " " << s[i] << endl;
            t1.push_back(s[i]);
            ++i;
            --j;
        } else if (f[i][j] == f[i + 1][j] + 1) { 
            //cout << "2" << " " << s[i] << endl;
            t1.push_back(s[i]);
            ++i;
        } else { 
           // cout << "3" << " " << s[j] << endl;
            t1.push_back(s[j]);
            --j;
        }
        cout << i << " " << j << endl;
    }

    if (i == j) {
        t1.push_back(s[i]);
    }

    int l = t1.size() - 1;

    if(i > j)
        l++;

    cout << t1 << endl;

    string t2 = t1.substr(0, l);
    reverse(t2.begin(), t2.end());
    t1 += t2;
}

int main()
{
    scanf("%s", 1+s);
    solve();
    build();
    cout << t1 << endl;
    return 0;
}
