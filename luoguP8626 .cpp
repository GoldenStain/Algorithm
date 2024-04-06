#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 50005, M = 2e5 + 5;

int n, m, q;

inline int read()
{
	int x = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		ch = getchar();
	while (ch >= '0' && ch <= '9')
		x = x * 10 + ch - '0', ch = getchar();
	return x;
}

// 最小生成树 并查集
int fa[N];
inline int find(int x)
{
	return x == fa[x] ? x : (fa[x] = find(fa[x]));
}

struct StrForEdge
{
	int _from, _to, w;
	bool operator<(const StrForEdge &_other) const
	{
		return w < _other.w;
	}
} Edge[M * 2];

//树边需要的一些数据成员
typedef pair<int, int> PII;
vector<PII> tree_edges[N];
// 连边
void on_tree_connect(int a, int b, int w)
{
	tree_edges[a].push_back({b, w});
	tree_edges[b].push_back({a, w});
}

void init_tree()
{
	// 初始化并查集
	for(int i = 1; i <= n; i++)
		fa[i] = i;
	
	int tree_cnt = 0;
	for(int i = 1; i <= m; i++)
	{
		int a = Edge[i]._from, b = Edge[i]._to;
		int pa = find(a), pb = find(b);
		if(pa != pb)
		{
			on_tree_connect(a, b, Edge[i].w);
			fa[pa] = pb;
			if(++tree_cnt == n - 1)
				return;
		}
	}
}

// 最小生成树
int lca_fa[N][17], maxw[N][17], depth[N];

void dfs_lca(int now, int Father)
{
	for(PII edge_on_tree : tree_edges[now])
	{
		 int v = edge_on_tree.first, w = edge_on_tree.second;
		 if(v == Father)
		 	continue;
		depth[v] = depth[now] + 1;
		lca_fa[v][0] = now;
		maxw[v][0]=w;
		for(int i=1;i<=16;i++)
		{
			lca_fa[v][i]=lca_fa[lca_fa[v][i-1]][i-1];
			maxw[v][i]=max(maxw[v][i-1],maxw[lca_fa[v][i-1]][i-1]);
		}
		dfs_lca(v, now);
	}
}

int link_on_tree(int a, int b)
{
	int res = -1;
	if(depth[a] < depth[b])
		swap(a, b);
	int d_of_depth = depth[a] - depth[b];
	for(int i = d_of_depth, Base = 0; i>0;i>>=1,Base++)
	{
		if(i & 1)
		{
			res = max(res, maxw[a][Base]);
			a = lca_fa[a][Base]; 
		}
	}
	if(a==b)
		return res;
	for(int i = 16; i>=0;i--)
		if(lca_fa[a][i]!=lca_fa[b][i])
		{
			res = max(res, maxw[a][i]);
			a = lca_fa[a][i];
			res = max(res, maxw[b][i]);
			b = lca_fa[b][i];
		}
	res = max(res, max(maxw[a][0], maxw[b][0]));
	return res;
}

void init_lca()
{
	// 以一号节点为根
	depth[1] = 1;
	dfs_lca(1, 0);
}

// 把询问离线，分辨建立线段树

struct StruForSegTree
{
	int l, r, maxx;
}SegTree[N*4];
//线段树的元数据
int DisofSegTree[N];

/*struct StruForQuery
{
	int l, r, k, c, id;
	bool operator < (const StruForQuery &_other)const
	{
		return k < _other.k;
	}
}Q[N];*/

void BuildSegTree(int now, int l, int r)
{
	SegTree[now] = {l, r, 0};
	if(l == r)
	{
		SegTree[now].maxx = DisofSegTree[l];
		return; 
	}
	int mid = (l + r) >> 1;
	int lson = now << 1, rson = now << 1 | 1;
	BuildSegTree(lson, l, mid);
	BuildSegTree(rson, mid + 1, r);
	SegTree[now].maxx = max(SegTree[lson].maxx, SegTree[rson].maxx);
}

void SmallInit(int k, int c)
{
	int L = 0, R = n, DataCnt = 0;
	for(int i = L/k*k+c; i + k <= R; i+=k)
	{
		if(i < L)	continue;
		DisofSegTree[++DataCnt] = link_on_tree(i, i + k);
	}
	BuildSegTree(1, 1, DataCnt);
}

int SegTreeQuery(int now, int l, int r)
{
	if(SegTree[now].l >= l && SegTree[now].r <= r)
		return SegTree[now].maxx;
	int mid = (SegTree[now].l + SegTree[now].r) >> 1;
	int res = -1;
	if(l <= mid)
		res = SegTreeQuery(now << 1, l, r);
	if(r > mid)
		res = max(res, SegTreeQuery(now << 1 | 1, l, r));
	return res;
}

int SmallQuery(int L, int R, int k, int c)
{
	int _offset = 1 + ((L-c)%k!=0);
	int l_to_query = (L-c)/k+_offset;
	if(L <= c)
		l_to_query = 1;
	int r_to_query = (R-c)/k;
	return SegTreeQuery(1, l_to_query, r_to_query);
}

int BigQuery(int l, int r, int k, int c)
{
	int L = l , R = r, ans = -1;
	for(int i = L/k*k+c; i + k <= R; i+=k)
	{
		if(i < L)	continue;
		ans = max(ans, link_on_tree(i, i + k));
	}
	return ans;
}

const int rN = 255;

//用来存储线段树中的询问
struct sQuery{
	int id, l, r;
};
vector<sQuery>	querys[rN][rN];

int ans[N];

int main()
{
	n = read();
	m = read();
	q = read();
	int tmpa, tmpb, tmpc;
	for (int i = 1; i <= m; i++)
	{
		tmpa = read();
		tmpb = read();
		tmpc = read();
		Edge[i] = {tmpa, tmpb, tmpc};
	}
	sort(Edge + 1, Edge + m + 1);
	init_tree();
	init_lca();
	int ql, qr, qk, qc;
	int Threshold = min(n/3, 110);
	for(int i = 1; i <= q; i++)
	{
		ql=read();qr=read();qk=read();qc=read();
		if(qk > Threshold)
			ans[i] = BigQuery(ql, qr, qk, qc);
		else
			querys[qk][qc].push_back({i, ql, qr});
	}
	/*for(int i = 1; i <= q; i++)
	{
		if(Q[i].k > Threshold)
		{
			ans[Q[i].id] = BigQuery(Q[i]);
			continue;
		}
		bool has_changed = false;
		if(know != Q[i].k)
			know = Q[i].k, has_changed = true;
		if(kc != Q[i].c)
			kc = Q[i].c, has_changed = true;
		ans[Q[i].id] = SmallQuery(Q[i], has_changed);
	}*/
	int cnt_ = 0;
	for(int i = 1; i <= Threshold; i++)
		for(int j = 0; j < i; j++)
		{
			if(querys[i][j].empty())
				continue;
			cnt_++;
			SmallInit(i, j);
			for(auto t:querys[i][j])
			{
				ans[t.id] = SmallQuery(t.l, t.r, i, j);
			}
		}
	cout << cnt_ << endl;
	for(int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
	return 0;
}
