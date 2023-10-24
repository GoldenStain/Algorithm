#include <iostream>
#include <cstring>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, string> PIS;

const int N = 105;

unordered_map<string, int> dist;
unordered_map<string, pair<char, string>> from;

string st, ed = "12345678x";

inline bool check(char t);

inline int e_value(string s)
{
    int res = 0;
    for (int i = 0; i < 9; i++)
    {
        if (s[i] == 'x')
            continue;
        int nx = i / 3, ny = i % 3;
        int rs = s[i] - '1'; // 因为下标从0开始，所以这里的rs也要从0开始
        int fx = rs / 3, fy = rs % 3;
        res += abs(nx - fx) + abs(ny - fy);
    }
    return res;
}

inline bool check(char t)
{
    if (t == 'x')
        return 1;
    if (isdigit(t))
        return 1;
    return 0;
}

void bfs(string st, string ed)
{
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    char dway[4] = {'u', 'r', 'd', 'l'};
    priority_queue<PIS, vector<PIS>, greater<PIS>> q;
    q.push({e_value(st), st});
    dist[st] = 0;
    while (q.size())
    {
        auto tmp = q.top();
        q.pop();
        string tmpc = tmp.second;
        if (tmpc == ed)
        {
            return;
        }
        int xpos;
        int dis = dist[tmpc];
        for (int i = 0; i < 9; i++)
            if (tmpc[i] == 'x')
            {
                xpos = i;
                break;
            }
        int nx = xpos / 3, ny = xpos % 3;
        for (int i = 0; i < 4; i++)
        {
            int fx = nx + dx[i], fy = ny + dy[i];
            if (fx < 0 || fx >= 3 || fy < 0 || fy >= 3)
                continue;
            int fpos = fx * 3 + fy;
            swap(tmpc[xpos], tmpc[fpos]);
            string after_move = tmpc;
            swap(tmpc[xpos], tmpc[fpos]);
            int dis_new = dis + 1;
            if (!dist.count(after_move) || dist[after_move] > dis_new)
            {

                q.push({e_value(after_move) + dis_new, after_move});
                dist[after_move] = dis_new;
                from[after_move] = {dway[i], tmpc};
            }
        }
    }
}

int main()
{
    string input;
    getline(cin, input);
    for (int i = 0; input[i]; i++) // 一开始忘记写i=0,虽然本地可以跑通，但是acwing上一直SF
    {
        if (check(input[i]))
            st += input[i];
    }
    int cnt = 0;
    for (int i = 0; i < 9; i++)
    {
        if (st[i] == 'x')
            continue;
        for (int j = i + 1; j < 9; j++)
            if (st[j] < st[i])
                cnt++;
    }
    if (cnt & 1)
    {
        puts("unsolvable");
    }
    else
    {
        bfs(st, ed);

        string ansv;
        while (ed != st)
        {
            ansv += from[ed].first;
            ed = from[ed].second;
        }
        reverse(ansv.begin(), ansv.end());
        cout << ansv << endl;
    }
    return 0;
}
