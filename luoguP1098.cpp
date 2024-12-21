#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <algorithm>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

template <typename T>
inline T read()
{
	T x = 0;
	int f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

int p[4];
string _input, _ans;
bool in_pos[105];

string _produce(char left, char right)
{
	string res = "";
	bool flag = true;
	int _offset = 0;
	if (left == right || left > right)
	{
		res.append(1, '-');
		return res;
	}
	switch (p[1])
	{
	case 1:
		break;
	case 2:
		if(!isdigit(left))
			_offset = -32;
		break;
	default:;
	}
	if (flag)
	{
		for (char i = left + 1; i < right; i++)
			res.append(p[2], i + _offset);
	}
	if (p[1] == 3)
		res.replace(0, res.length(), string(res.length(), '*'));
	if (p[3] == 2)
		reverse(res.begin(), res.end());
	return res;
}

bool check(string str, int pos)
{
	if (pos < 1)
		return false;
	return (str[pos] == '-') && ((isdigit(str[pos - 1]) && isdigit(str[pos + 1])) | (isalpha(str[pos + 1]) && isalpha(str[pos - 1])));
}

int main()
{
	for (int i = 1; i <= 3; i++)
		cin >> p[i];
	cin >> _input;
	_ans = "";
	for (int i = 0; i < _input.length(); i++)
	{
		if (check(_input, i))
		{
			_ans += _produce(_input[i - 1], _input[i + 1]);
		}
		else
			_ans.append(1, _input[i]);
	}
	cout << _ans << endl;
	return 0;
}
