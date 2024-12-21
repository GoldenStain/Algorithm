#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int N = 105;

int g[N][N];
char _map[N][N];
int n, m;

int get_mines(int x, int y)
{
    if(_map[x][y] == '*')
        return -1;
    int count = 0;
    for(int i = x - 1; i <= x + 1; i++)
        for(int j = y - 1; j <= y + 1; j++)
        {
            if(i < 0 || i >= n || j < 0 || j >= m)
                continue;
            if(i == x && j == y)
                continue;
            count += (_map[i][j] == '*');
        }
    return count;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)
        scanf("%s", _map[i]);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            g[i][j] = get_mines(i, j);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            if(g[i][j] < 0)
                putchar('*');
            else 
                printf("%d", g[i][j]);
        puts("");
    }
    return 0;
}