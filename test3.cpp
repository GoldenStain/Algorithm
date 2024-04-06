#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;
int m[5000][5000] = {};
void p(int n);
int g;
void gen(int n, int x, int y)
{
    if (n == 1)
    {
        m[y][x] = 1;
        m[y][x + 1] = 2;
        m[y + 1][x - 1] = 1;
        m[y + 1][x] = 3;
        m[y + 1][x + 1] = 3;
        m[y + 1][x + 2] = 2;
    }
    else
    {
        gen(n - 1, x, y);
        p(g);
        gen(n - 1, x - (1<<(n - 1)), y + (1<<(n - 1)));
        p(g);
        gen(n - 1, x + (1<<(n - 1)), y + (1<<(n - 1)));
        p(g);
    }
    puts("\n\n");
}
void p(int n)
{
    for (int i = 1; i <= (1<<n); i++)
    {
        for (int j = 1; j <= pow(2, n + 1); j++)
            if (!m[i][j])
                m[i][j] = 4;
    }
    for (int i = 1; i <= (1<<n); i++)
    {
        for (int j = 1; j <= (1<<n) + i; j++)
        {
            if (m[i][j] == 1)
                cout << "/";
            else if (m[i][j] == 2)
                cout << "\\";
            else if (m[i][j] == 3)
                cout << "_";
            else if (m[i][j] == 4)
                cout << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    g=n;
    gen(n, (1<<n), 1);

    return 0;
}
