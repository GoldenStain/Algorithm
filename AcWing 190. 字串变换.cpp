#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <queue>

using namespace std;

typedef pair<string, int> PSI;

const int N = 25;

string sa, sb;
int n;
string ra[N], rb[N];

int extend(queue<string> &q, unordered_map<string, int> &da, unordered_map<string, int> &db, string ra[], string rb[])
{
    int d0 = da[q.front()];
    while (q.size() && da[q.front()] == d0)
    {
        string st = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            size_t StartPos = 0; //要放在这个i循环的内部，每次换pattern串都要从零开始
            size_t pos = st.find(ra[i], StartPos);
            int tmp_len = ra[i].size();
            while (pos != string::npos)
            {
                string ns = st.substr(0, pos) + rb[i] + st.substr(pos + tmp_len);
                StartPos = pos + 1;
                if (db.count(ns))
                    return d0 + db[ns] + 1;
                if (!da.count(ns))
                {
                    da[ns] = d0 + 1;
                    q.push(ns);
                }
                pos = st.find(ra[i], StartPos);
            }
        }
    }
    return 11;//前面不一定能找到，这里也要加一个return
}

int bfs()
{
    if (sa == sb)
    {
        return 0;
    } // 相等就不用搜索了
    queue<string> qa, qb;
    unordered_map<string, int> da, db;
    qa.push(sa);
    qb.push(sb);
    da[sa] = 0;
    db[sb] = 0;
    int step = 0;
    while (qa.size() && qb.size())
    {
        int t;
        if (qa.size() < qb.size())      
            t = extend(qa, da, db, ra, rb);
        else
            t = extend(qb, db, da, rb, ra);
        if (t <= 10)
            return t;
        if (++step > 10)
            return -1;
    }
    return -1;
}

int main()
{
    cin >> sa >> sb;
    while (cin >> ra[n] >> rb[n])
        n++;
    int ans = -1;
    ans = bfs();
    if (ans == -1)
        puts("NO ANSWER!");
    else
        cout << ans << endl;
    return 0;
}