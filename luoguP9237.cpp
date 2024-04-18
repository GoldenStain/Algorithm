#include<bits/stdc++.h>
using namespace std;
const int S=15,N=10,M=1<<22,INF=0x3f3f3f3f;
int n,m,a[S][S],b[S][S],cur[S][S];
bitset<M>dp[N][N];
char s[S][S];
bool ok;
bool in(int x,int y){
	return 0<=x && x<n && 0<=y && y<m && a[x][y]!=INF;
}
bool can(int x,int y,int v){
	for(int i=-1;i<=1;++i){
		for(int j=-1;j<=1;++j){
			int nx=x+i,ny=y+j;
			if(in(nx,ny) && cur[nx][ny]+v>a[nx][ny])return 0;
		}
	}
	if(in(x-1,y-1) && cur[x-1][y-1]+v<a[x-1][y-1])return 0;
	if(x==n-1 && in(x,y-1) && cur[x][y-1]+v<a[x][y-1])return 0;
	if(y==m-1 && in(x-1,y) && cur[x-1][y]+v<a[x-1][y])return 0;
	return 1;
}
void dfs(int x,int y,int w){
	//cnt++;
    cout << x << " " << y << " " << w << endl;
	if(x==n && y==0){
		ok=1;
		for(int i=0;i<n;++i){
			for(int j=0;j<m;++j){
				printf("%d",b[i][j]);
			}
			puts("");
		}
		return;
	}
	if(ok)return;
	if(dp[x][y][w])return;
	dp[x][y][w]=1;
	for(int v=1;v>=0;--v){
		if(ok)return;
		if(can(x,y,v)){
			b[x][y]=v;
			if(v){
				for(int i=-1;i<=1;++i){
					for(int j=-1;j<=1;++j){
						int nx=x+i,ny=y+j;
						if(!in(nx,ny))continue;
						cur[nx][ny]++;
					}
				}
			}
			int nw=(w<<1)|v;
			if(y==m-1)dfs(x+1,0,nw&((1<<(2*m))-1));
			else dfs(x,y+1,nw&((1<<(2*m+2))-1));
			if(v){
				for(int i=-1;i<=1;++i){
					for(int j=-1;j<=1;++j){
						int nx=x+i,ny=y+j;
						if(!in(nx,ny))continue;
						cur[nx][ny]--;
					}
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i){
		scanf("%s",s[i]);
		for(int j=0;j<m;++j){
			a[i][j]=INF;
			if(s[i][j]!='_')a[i][j]=s[i][j]-'0';
		}
	}
	dfs(0,0,0);
	//printf("cnt:%d\n",cnt);
	return 0;
}