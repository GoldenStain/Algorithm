#include <bits/stdc++.h>
using namespace std;
long long x, y, n, d;
int main() {
	cin >> x >> y;
	n = max(abs(x), abs(y)), d = 2*n*(2*n+1);
	if (y >= 0 && abs(x) <= y) cout << d-3*n+x;//上部分 
	else if (y < 0 && y < x && x <= -y) cout << d+n-x;//下部分 
	else if (x >= 0 && abs(y) <= x) cout << d-n-y;//右部分 
	else if (x < 0 && x < y && y <= -x) cout << d-5*n+y;//左部分 
	return 0;
}