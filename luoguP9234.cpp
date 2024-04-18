#include<cstdio>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#define ll long long
#define re register
#define il inline
#define INF 2147483647

using namespace std;

il int read() { // 快读
	re int x = 0, f = 1; re char c = getchar();
	while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
	while(c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f; }

int n, m, ans, N, a[35];
unordered_map<int, int> q;

il void dfs1(int cnt, int sum, int num) {
	// 	cnt表示第几个瓜，sum表示当前买的瓜的总重量，num表示砍了多少刀
	if(sum > m || num > ans) return ;
	//	如果当前重量大于m，不用搜了，直接返回
	// 	如果当前砍瓜次数已经大于目前最优值ans，不用搜了，直接返回
	if(sum == m) { // 如果当前重量刚好等于m
		ans = ans < num ? ans : num; // 更新ans
		return ;
	}
	if(cnt == N + 1) {
		if(sum <= m) {
			if(q.count(sum)) // 查找sum在unordered_map中是否出现
				q[sum] = q[sum] < num ? q[sum] : num;
			else 
				q[sum] = num;
			// 当前重量为sum时最少要砍多少刀
		}
		return ;
	}
	dfs1(cnt + 1, sum, num); // 不买这个瓜
	dfs1(cnt + 1, sum + a[cnt], num + 1); // 买一半瓜
	dfs1(cnt + 1, sum + (a[cnt] << 1), num); // 买整个瓜
	//	a[cnt] << 1 等价于 a[cnt] * 2
}

il void dfs2(int cnt, int sum, int num) {
	// 	cnt表示第几个瓜，sum表示当前买的瓜的总重量，num表示砍了多少刀
	if(sum > m || num > ans) return ;
	//	如果当前重量大于m，不用搜了，直接返回
	// 	如果当前砍瓜次数已经大于目前最优值ans，不用搜了，直接返回
	if(sum == m) { // 如果当前重量刚好等于m
		ans = ans < num ? ans : num;// 更新ans
		return ;
	}
	if(cnt == n + 1) {
		if(q.count(m - sum) && sum <= m) 
			ans = ans < (q[m - sum] + num) ? ans : (q[m - sum] + num); // 更新ans
		return ;
	}
	dfs2(cnt + 1, sum, num); // 不要这个瓜
	dfs2(cnt + 1, sum + a[cnt], num + 1); // 买一半瓜
	dfs2(cnt + 1, sum + (a[cnt] << 1), num); // 买整个瓜
}

int main() {
	n = read(), m = read();
	for(re int i = 1; i <= n; ++ i) a[i] = read();
	m = (m << 1); // 等价于 m *= 2;
	//	防止浮点精度爆炸，把m乘2
	N = (n >> 1); // 等价于 n /= 2;
	sort(a + 1, a + 1 + n); // 优化搜索顺序
	ans = INF; // 求最小值，ans初始值为最大值
	dfs1(1, 0, 0); // 折半搜索
	dfs2(N + 1, 0, 0);
	printf("%d", ans == INF ? -1 : ans);
	//	如果ans没有被更新，说明不可能买到重量恰好为m的瓜，就输出-1
	return 0;
}