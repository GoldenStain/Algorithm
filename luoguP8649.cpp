#include <iostream>
#include <map>
#define int long long
using namespace std;

map <int, int> mp; //记录每个余数出现个数的数组

signed main()
{
	int n, k, ans = 0;
	cin >> n >> k;
	mp[0] = 1; //初始化 0 出现的次数为 1
	for(int i = 1;i <= n;i++)
	{
		int x;
		cin >> x;
		ans += (x % k); //计算前缀和
		mp[ans % k]++; //前缀和模 k
		ans %= k;
	}
	int cnt = 0;
	for(int i = 0;i < k;i++) cnt += (mp[i] * (mp[i] - 1)) / 2; //根据上述公式计算答案
	cout << cnt << endl;
	return 0;
}