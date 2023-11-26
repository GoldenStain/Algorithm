#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int x;
int find_less(vector<int> &v, int x)
{
    int step = 0;
    int l = 0, r = v.size() - 1;
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(v[mid] < x) l = mid;
        else r = mid - 1;
    }
    if(v[l] > x) return l;
    return 100;
}
int main()
{
    vector<int> a;
    a = {1, 2, 3, 5, 7};
    int tmp = find_less(a, 6);
    cout << tmp << endl;
    cout << a[tmp] << endl;
    system("pause");
    return 0;
}