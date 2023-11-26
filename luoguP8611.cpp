#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

const int N = 55;

int n, x0, st;
vector<int> r, l;

int find_less(vector<int> &v, int x)
{
    int l = 0, r = v.size() - 1;
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(v[mid] < x) l = mid;
        else r = mid - 1;
    }
    if(v[l] < x) return l;
    return 100;
}

int find_greater(vector<int> &v, int x)
{
    int l = 0, r = v.size() - 1;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(v[mid] > x) r = mid;
        else l = mid + 1;
    }
    if(v[l] > x) return l;
    return 100;
}

int main()
{
    priority_queue<int, vector<int>, greater<int>> q;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (i == 1)
            x0 = x;
        if (x < 0)
        {
            l.push_back(-x);
        }
        else
        {
            r.push_back(x);
        }
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    /*cout << "right: ";
    for (auto i : r)
        cout << i << " ";
    cout << "\n";
    cout << "left:  ";
    for (auto i : l)
        cout << i << " ";
    cout << "\n";*/
    st = abs(x0);
    int rp, lp;
    int ans = 0;
    if (x0 > 0)
    {
        rp = st;
        int tmp = find_greater(l, rp);
        if (tmp >= 0 && tmp < l.size())
        {
            lp = l[tmp];
            ans += l.size() - tmp;
            tmp = find_less(r, lp);
            ans += tmp + 1;
        }
    }
    else
    {
        lp = st;
        int tmp = find_less(r, lp);
        if(tmp >= 0 && tmp <r.size())
        {
            rp = r[tmp];
            //cout << tmp << endl;
            ans += tmp + 1;
            tmp = find_greater(l, rp);
            ans += l.size() - tmp;
        }
    }
    cout << (ans?ans:1) << endl;
    system("pause");
    return 0;
}