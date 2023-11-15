#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <cstring>
#include <vector>
using namespace std;

const int N = 25;

int n, ans, cnt[N];
string s[N];

int check(string a, string b, int lena, int lenb) // a是倒着，b是顺序
{
    int l = min(lena, lenb);
    int i;
    int ans;
    for (i = 1; i < l; i++)
    {
        bool flag = 1;
        for (int j = 0; j < i; j++)
            if (a[lena - i + j] != b[j])
            {
                flag = false;
                break;
            }
        if (flag)
        {
            return i;
        }
    }
    return 0;
}

void dfs(int u, int now)
{
    bool flag = false;
    ans = max(ans, now);
    for (int i = 1; i <= n; i++)
    {
        if (cnt[i] >= 2)
            continue;
        int lena = s[u].length(), lenb = s[i].length();
        int tmp = check(s[u], s[i], lena, lenb);
        if (tmp < 1)
            continue;
        flag = true;
        cnt[i]++;
        dfs(i, now + lenb - tmp);
        cnt[i]--;
    }
    if (!flag)
    {
        return;
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    cin >> s[0];
    s[0] = " " + s[0];
    dfs(0, 1);
    cout << ans << endl;
    return 0;
}