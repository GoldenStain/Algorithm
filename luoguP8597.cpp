#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <cstring>
using namespace std;

const int N = 1005;

char s[N], t[N];
int pos[N], hh, cnt, tt;

int main()
{
    scanf("%s%s", s, t);
    int l = strlen(s);
    hh = 0;
    tt = 0;
    for (int i = 0; i < l; i++)
        if (s[i] != t[i])
            pos[tt++] = i;
    cnt = tt;
    pos[tt++] = 114514;
    int ans = 0;
    while(cnt)
    {
        if(pos[hh] + 1 == pos[hh + 1])
        {
            ans++;
            cnt -= 2;
            hh += 2;
        }
        else
        {
            ans++;
            pos[hh] = pos[hh] + 1;
        }
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}