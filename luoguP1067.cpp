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
	T f = 1; char ch = getchar();
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

int x, cnt;

int main()
{
	cin >> cnt;
	for(int i = cnt; i >= 0; i--)
	{
		cin >> x;
		if(x == 0)
			continue;
		int t = abs(x);
		if(x > 0 && i < cnt)
			cout << "+";
		else if(x < 0)
			cout << "-";
		if(t > 1 || i == 0)
			cout << t;
		if(i > 0)
		{
			cout << "x";
			if(i > 1)
				cout << "^" << i;
		}
	}
	return 0;
}
