#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

vector<int> a;

int main()
{   
    a.push_back(1);
    a.back() ++;
    cout << a[0] << endl;
    return 0;
}
