#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

template <typename T>
inline T read()
{
    T x = 0;
    int f = 1; char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
       x = x * 10 + ch - '0';
       ch = getchar();
    }
    return x * f;
}

const int N = 1005;

int n;
struct Question{
    int id, difficulty;
    bool operator < (const Question& _another) const 
    {
        if(difficulty == _another.difficulty)
            return id < _another.id;
        return difficulty < _another.difficulty;
    }
}a[N];

int main()
{
    n = read<int>();
    for(int i = 1; i <= n; i++)
        a[i].difficulty = read<int>(), a[i].id = i;
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++)
        printf("%d ", a[i].id);
    return 0;
}
