#include<bits/stdc++.h>
#define rep(a,b,c) for(int c(a);c<=(b);++c)
#define drep(a,b,c) for(int c(a);c>=(b);--c)
using namespace std;
inline int read()
{
	int res=0;char ch=getchar();while(ch<'0'||ch>'9')ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();return res;
}
typedef long long ll;
const int N=5e4+10,M=1e5+5;
int a[N],n,mn[N],mx[N],cnt[N<<2];ll ans;
inline void Solve(int l,int r)
{
	if(l==r){++ans;return;} int mid=(l+r)>>1;
	mn[mid+1]=a[mid+1];mx[mid+1]=a[mid+1];
	rep(mid+2,r,i)mn[i]=min(mn[i-1],a[i]),mx[i]=max(mx[i-1],a[i]);
	mn[mid]=a[mid];mx[mid]=a[mid];
	drep(mid-1,l,i)mn[i]=min(mn[i+1],a[i]),mx[i]=max(mx[i+1],a[i]);
	int pr=mid+1,ppr=mid+1;drep(mid,l,pl)
	{
		while(pr<=r&&mx[pr]<mx[pl]){++cnt[mn[pr]+pr+M];++pr;}
		while(ppr<pr&&mn[ppr]>mn[pl]){--cnt[mn[ppr]+ppr+M];++ppr;}
		ans+=cnt[mx[pl]+pl+M];int tr=mx[pl]+pl-mn[pl];
		if(mid<tr&&tr<ppr)++ans;
	}
	for(int i=ppr;i<pr;++i)cnt[mn[i]+i+M]=0;
	int pl=mid,ppl=mid;rep(mid+1,r,pr)
	{
		while(pl>=l&&mx[pl]<mx[pr]){++cnt[mn[pl]-pl+M];--pl;}
		while(ppl>pl&&mn[ppl]>mn[pr]){--cnt[mn[ppl]-ppl+M];--ppl;}
		ans+=cnt[mx[pr]-pr+M];int tl=mn[pr]-mx[pr]+pr;
		if(ppl<tl&&tl<=mid)++ans;
	}
	for(int i=ppl;i>pl;--i)cnt[mn[i]-i+M]=0;
	Solve(l,mid);Solve(mid+1,r);
}
int main()
{
	n=read();rep(1,n,i)a[i]=read();
	Solve(1,n);printf("%lld\n",ans);
}