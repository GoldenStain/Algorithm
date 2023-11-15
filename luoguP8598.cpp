#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <cstring>
#include <sstream>
using namespace std;

const int N = 1e5 + 5;
int t, n, a[N];
string s;

int main()
{
    cin >> t;
    int Min = N, Max = 0;
    getline(cin, s);
    while(t--)
    {
        int x;
        getline(cin, s);
        stringstream ssin(s);
        while(ssin >> x)
        {
            a[x]++;
            Min = min(Min, x);
            Max = max(Max, x);
        }
    }
    int f1 = 0, f2 = 0;
    for (int i = Min; i <= Max; i++)
    {
        if (f2 && f1)
            break;
        if (!a[i])
        {
            f1 = i;
        }
        if (a[i] > 1)
            f2 = i;
    }
    printf("%d %d\n", f1, f2);
    system("pause");
    return 0;
}