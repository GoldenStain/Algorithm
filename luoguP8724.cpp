#include<bits/stdc++.h>
#define int long long
using namespace std;
struct a1{
	int nex,to,dis;
}x[4000001];
int dis[400001],head[400001],p=0,v[400001];
void add(int a,int b,int c){
	x[++p].nex=head[a];
	x[p].to=b;
	x[p].dis=c;
	head[a]=p;
	return ;
}
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
	return x*f;
}
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >z;
int pre[1000001];
signed main(){
	int n,m;
	n=read();m=read();
	for(int q=1;q<=m;q++){
		int a,b,c,d;
		a=read();b=read();c=read();d=read();
		if(d==1){//有限高杆
			add(a,b+n,c);//第一层和第二层相连，注意是从上往下连，第一层中的a和第二层中的b相连，第一层中的b和第二层中的a相连。
			add(b,a+n,c);
			add(b+n,a+n+n,c);//同上
			add(a+n,b+n+n,c);
		}
		else{//无限高杆
			add(a,b,c);
			add(b,a,c);
			add(b+n,a+n,c);
			add(a+n,b+n,c);
			add(b+n+n,a+n+n,c);
			add(a+n+n,b+n+n,c);
		}
	}
	fill(dis,dis+1+n*3,1e9);//三层图三倍数组初始化
	z.push(make_pair(0,1));
	dis[1]=0;
	while(!z.empty()){
		int i=z.top().second;
		z.pop();
		if(v[i])continue;
		v[i]=1;
		for(int q=head[i];q;q=x[q].nex){
			int o=x[q].to;
			if(dis[o]>dis[i]+x[q].dis){
				dis[o]=dis[i]+x[q].dis;
				pre[o]=i;
				z.push(make_pair(dis[o],o));
			}
		}
	}//单源最短路模板
	cout<<dis[n]-min(dis[n*3],min(dis[n],dis[n*2]));;//注意最短路不一定要拆两个限高杆
	return 0;
}