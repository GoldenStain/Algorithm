#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int N = 105;

bool ans[N];
int n, t, k, x, path[N];

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        memset(path, 0, sizeof(path));
        memset(ans, 0, sizeof(ans));
        scanf("%d%d%d", &n, &k, &x);
        ans[0] = 1;
        for (int i = 1; i <= k; i++)
        {
            if (i == x)
                continue;
            for (int j = i; j <= n; j++)
            {
                bool tmp = ans[j];
                ans[j] = ans[j - i] | ans[j];
                if (ans[j] && !tmp)
                    path[j] = i;
            }
        }
        if (!ans[n])
        {
            puts("NO");
            continue;
        }
        else
        {
            puts("YES");
            vector <int> sequence;
            while (n)
            {
                sequence.push_back(path[n]);
                n -= path[n];
            }
            printf("%d\n", sequence.size());
            for(auto t : sequence)
             printf("%d ",t);
            putchar('\n');
        }
    }
    system("pause");
    return 0;
}