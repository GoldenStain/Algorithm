#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <string.h>
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;
using namespace std;
int e1, e2, x1, x2;
int a1[6], a2[6];
int t1[5], t2[5];
int f1[6], f2[6];
int flag;
int Min;
int path1[6];
int path2[6];
int enter;
vector<double> arr;
void init()
{
    cin >> e1 >> e2 >> x1 >> x2;
    for (int i = 1; i <= 5; i++)
        cin >> a1[i];
    for (int i = 1; i <= 5; i++)
        cin >> a2[i];
    for (int i = 1; i <= 4; i++)
        cin >> t1[i];
    for (int i = 1; i <= 4; i++)
        cin >> t2[i];
}
int main()
{
    init();
    for (int i = 1; i <= 5; i++)
    {
        if (i == 1)
        {
            f1[i] = e1 + a1[1];
            f2[i] = e2 + a2[1];
        }
        else
        {
            f1[i] = min(f1[i - 1] + a1[i], f2[i - 1] + t2[i - 1] + a1[i]);
            if (f1[i - 1] + a1[i] < f2[i - 1] + t2[i - 1] + a1[i])
                path1[i] = 1;
            else
                path1[i] = 2;
            f2[i] = min(f2[i - 1] + a2[i], f1[i - 1] + t1[i - 1] + a2[i]);
            if (f2[i - 1] + a2[i] < f1[i - 1] + t1[i - 1] + a2[i])
                path2[i] = 2;
            else
                path2[i] = 1;
        }
        Min = min(f1[5] + x1, f2[5] + x2);
        if (f1[5] + x1 < f2[5] + x2)
            flag = 1;
        else
            flag = 2;
    }
    for (int i = 1; i <= 5; i++)
    {
        cout << f1[i] << " " << f2[i] << endl;
    }
    cout << Min << endl;
    if (flag == 1)
        //printf("s1.5 ");
        arr.push_back(1.5);
    else if (flag == 2)
        arr.push_back(2.5);
    for (int i = 5; i >= 2; i--)
    {
        if (flag == 1)
        {
            if (path1[i] == 1)
            {
                cout << 1 <<endl;
                //printf("s1.%d ", i - 1);
                arr.push_back(1 + (i-1)*0.1);
                flag = 1;
            }
            else if (path1[i] == 2)
            {
                cout << 2 << endl;
                //printf("s2.%d ", i - 1);
                arr.push_back(2 + (i-1)*0.1);
                flag = 2;
            }
        }
        else if (flag == 2)
        {
            if (path2[i] == 1)
            {
                cout << 3 << endl;
                //printf("s1.%d ", i - 1);
                arr.push_back(1 + (i-1)*0.1);
                flag = 1;
            }
            else if (path2[i] == 2)
            {
                cout << 4 << endl;
                //printf("s2.%d ", i - 1);
                arr.push_back(2 + (i-1)*0.1);
                flag = 2;
            }
        }
    }
    reverse(arr.begin(), arr.end());
    for(auto i:arr)
        cout << i << " ";
    return 0;
}