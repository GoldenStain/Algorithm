#include <iostream>
#include <map>
#define int long long
using namespace std;

map <int, int> mp; //��¼ÿ���������ָ���������

signed main()
{
	int n, k, ans = 0;
	cin >> n >> k;
	mp[0] = 1; //��ʼ�� 0 ���ֵĴ���Ϊ 1
	for(int i = 1;i <= n;i++)
	{
		int x;
		cin >> x;
		ans += (x % k); //����ǰ׺��
		mp[ans % k]++; //ǰ׺��ģ k
		ans %= k;
	}
	int cnt = 0;
	for(int i = 0;i < k;i++) cnt += (mp[i] * (mp[i] - 1)) / 2; //����������ʽ�����
	cout << cnt << endl;
	return 0;
}