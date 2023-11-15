#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#define R register
using namespace std;
const int N = 255;
int g[N][N];
int f[N][N];
int n, m, res;
int main()
{  
    double sum = 0;
    for(int i = 1; i <= 6; i++)
    {
        int x, y;
        cin >> x >> y;
        sum += (double)(x + y) / 2;
    }
    sum /= 6;
    cout << sum * 0.7 << endl;
    system("pause");
    return 0;
}