#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 505, M = 25010, INF = 0x3f3f3f3f;
int m, n;
int f[N][N];
inline void DealWith(string os)
{
    vector<int> v;
    for (int i = 0; i < os.size(); i++)
    {
        if (isdigit(os[i]))
        {
            int x = 0;
            while (isdigit(os[i]))
            {
                x = x * 10 + os[i] - '0';
                i++;
            }
            i--;
            v.push_back(x);
        }
    }
    #ifdef DEBUG
    for(auto i:v) cout << i << ' ';
    cout << endl;
    #endif
    int s = v.size();
    for (int i = 0; i < s; i++)
        for (int j = i + 1; j < s; j++)
        {
            int a = v[i], b = v[j];
            f[a][b]   = min(f[a][b], 1);
        }
}
int main()
{
    string os;
    memset(f, 0x3f, sizeof(f));
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        f[i][i] = 0;
    getline(cin,os);
    for (int i = 1; i <= m; i++)
    {
        getline(cin, os);
        DealWith(os);
    }
    #ifdef DEBGU
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int x = f[i][j] == INF ? -1 : f[i][j];
            cout << x << ' ';
        }

        cout << "\n";
    }
    #endif
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    if(f[1][n]>INF/2) cout << "NO" << "\n";
    else cout << f[1][n] - 1 << "\n";
    system("pause");
    return 0;
}