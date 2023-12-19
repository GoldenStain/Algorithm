#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

int w, m, n, x_m, y_m, x_n, y_n;

void get(int p, int &x, int &y)
{
    x = (p + w - 1) / w;
    int tmp = p % w;
    int cnt = (tmp) ? tmp : w;
    if(x & 1) y = cnt;
    else y = w - cnt + 1;
}

int main()
{
    cin >> w >> m >> n;
    get(m, x_m, y_m);
    get(n, x_n, y_n);
    cout << abs(x_m - x_n) + abs(y_m - y_n);
    system("pause");
    return 0;
}
