#include<bits/stdc++.h>
using namespace std;

int read()
{
	char c=getchar(); int res=0, f=1;
	while(!isdigit(c)) {if(c=='-') f=-1; c=getchar();}
	while(isdigit(c)) {res=(res<<3)+(res<<1)+(c^48); c=getchar();}
	return res*f;
}

const int N=5e4+1, M=2e5+1;

int n,m,q,thre;

struct Edge {int x,y,z;} E[M];
bool cmpz(Edge a, Edge b) {return a.z < b.z;}

int Fa[N];
int find(int x) {return Fa[x]==x ? x:Fa[x]=find(Fa[x]);}
int merge(int x,int y)
{
	int fx=find(x), fy=find(y);
	if(fx!=fy) {Fa[fx]=fy; return 1;}
	return 0;
}

struct edge {int nex,to,v;} a[N<<1];
int h[N],tot;
void adde(int x,int y,int z)
{
	a[++tot]=(edge){h[x],y,z}, h[x]=tot;
	a[++tot]=(edge){h[y],x,z}, h[y]=tot;
}

int dep[N],val[N],sq[N<<1],Ti,in[N];
void dfs_init(int u,int f)
{
	dep[u]=dep[f]+1, sq[in[u]=++Ti]=u;
	for(int i=h[u];i;i=a[i].nex)
	{
		int v=a[i].to;
		if(v!=f) val[v]=a[i].v, dfs_init(v,u), sq[++Ti]=u;
	}
}
#define _min(x,y) (in[x]<in[y] ? x:y)
int lg2[N<<1],minn[N<<1][18];
void build_ST()
{
	lg2[0]=-1;
	for(int i=1;i<=Ti;++i) lg2[i]=lg2[i>>1]+1, minn[i][0]=sq[i];
	for(int i=1;(1<<i)<=Ti;++i)
	for(int l=1;l+(1<<i)-1<=Ti;++l)
		minn[l][i] = _min(minn[l][i-1], minn[l+(1<<(i-1))][i-1]);
}
int LCA(int x,int y)
{
	x=in[x], y=in[y];
	if(x>y) swap(x,y);
	int k=lg2[y-x+1];
	return _min(minn[x][k], minn[y-(1<<k)+1][k]);
}
#undef _min

struct Que {int l,r,K,C,id;} lx[N]; int Q,answer[N];
bool cmpq(Que a,Que b) {return a.K < b.K;}

struct data {int v,id;};
vector<data> G[N]; int ans[N*100],block,blo[N];
pair<int,int> sta[N]; int top;

void addq(int u,int v,int id)
{
	int lca=LCA(u,v);
	G[u].emplace_back((data){lca,id});
	G[v].emplace_back((data){lca,id});
}

int maxx[N<<2],A[N];
void add(int u,int v)
{
	int p=blo[u];
	for(int i=1;i<blo[u];++i) sta[++top] = make_pair(i,maxx[i]), maxx[i] = max(maxx[i],v);
	for(int i=(p-1)*block+1; i<=u; ++i) sta[++top] = make_pair(-i,A[i]), A[i] = max(A[i],v);
}
int ask(int u) {return max(maxx[blo[u]], A[u]);}
void roll_back(int tar)
{
	while(top>tar)
	{
		int i=sta[top].first, v=sta[top].second; --top;
		if(i>0) maxx[i]=v; else A[-i]=v;
	}
}
void dfs_calc(int u,int f)
{
	int prev=top;
	add(dep[u],val[u]);
	for(auto now : G[u])
	{
		int v=now.v, id=now.id;
		if(id>0) answer[id] = max(answer[id], ask(dep[v]+1));
		else ans[-id] = max(ans[-id], ask(dep[v]+1));
	}
	for(int i=h[u];i;i=a[i].nex)
	{
		int v=a[i].to;
		if(v!=f) dfs_calc(v,u);
	}
	roll_back(prev);
}

#define ls (pos<<1)
#define rs (pos<<1|1)
#define mid ((l+r)>>1)
void build(int pos,int l,int r)
{
	if(l==r) {maxx[pos]=A[l]; return;}
	build(ls,l,mid); build(rs,mid+1,r);
	maxx[pos] = max(maxx[ls],maxx[rs]);
}
int ask(int pos,int ql,int qr,int l,int r)
{
	if(ql>qr) return 0;
	if(ql<=l && r<=qr) return maxx[pos];
	int res=0;
	if(ql<=mid) res = max(res, ask(ls,ql,qr,l,mid));
	if(qr>mid) res = max(res, ask(rs,ql,qr,mid+1,r));
	return res;
}
#undef ls
#undef rs
#undef mid

int id[N];
int main()
{
	n=read(), m=read(), q=read();
	for(int i=1;i<=m;++i)
		E[i]=(Edge){read(),read(),read()};
	sort(E+1,E+m+1,cmpz);
	for(int i=1;i<=n;++i) Fa[i]=i;
	for(int i=1;i<=m;++i)
	{
		if(merge(E[i].x, E[i].y))
			adde(E[i].x, E[i].y, E[i].z);
	}
	dfs_init(1,0); build_ST();
	thre=100;
	for(int i=1,l,r,K,C;i<=q;++i)
	{
		l=read(), r=read(), K=read(), C=read();
		if(K>thre)
		{
			for(int u=(l-1)/K*K+C,v=0; u<=r; u+=K)
			{
				if(u<l) continue;
				if(v) addq(u,v,i); v=u;
			}
		}
		else lx[++Q]=(Que){l,r,K,C,i};
	}
	sort(lx+1,lx+Q+1,cmpq);
	
	for(int i=1,tt=0,K=0;i<=Q;++i)
	{
		if(lx[i].K!=K)
		{
			K=lx[i].K;
			for(int C=0;C<K;++C)
			for(int u=C?C:K,v=0; u<=n; v=u,u+=K)
			{
				++tt;
				if(v) addq(u,v,-tt);
			}
		}
	}
	block=sqrt(n);
	for(int i=1;i<=n;++i) blo[i]=(i-1)/block+1;
	dfs_calc(1,0);
	
	for(int i=1,tt=0,K=0;i<=Q;++i)
	{
		if(lx[i].K!=K)
		{
			K=lx[i].K;
			int prev=tt;
			for(int C=0;C<K;++C)
			for(int u=C?C:K;u<=n;u+=K)
			{
				++tt;
				A[tt-prev]=ans[tt], id[u]=tt-prev;
			}
			build(1,1,n);
		}
		int l = (lx[i].l-1)/K*K+lx[i].C;
		if(l<lx[i].l) l+=K;
		int r = lx[i].r/K*K+lx[i].C;
		if(r>lx[i].r) r-=K;
		if(l<=r) answer[lx[i].id] = ask(1,id[l]+1,id[r],1,n);
	}
	for(int i=1;i<=q;++i) printf("%d\n",answer[i]);
}