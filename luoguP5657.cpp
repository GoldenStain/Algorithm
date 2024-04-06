#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

typedef unsigned long long Ull;
const unsigned long long LIM = 18446744073709551615ull;

Ull k;
int n;

int main()
{
    cin >> n >> k;
    Ull res = 0;
    while(n)
    {
        //cout << "\nk :" << k << endl;
        Ull now = 1ull << (n - 1);
        //cout << "\nnow :" << now << endl;
        if(k < now)
            putchar('0');
        else
            putchar('1');
        if(k >= now)
            //k = (1 << n) - k - 1;
        {
            if(n == 64)
                k = LIM - k;
            else 
                k = (1ull << n) - k - 1;
        }
        n--;
    }
    return 0;
}