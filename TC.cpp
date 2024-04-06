#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int t = n + m;
    if((n + m) & 1 == 0)
        cout << (n + m)/2;
    else
        cout << (n + m + 1)/2;
    return 0;
}
