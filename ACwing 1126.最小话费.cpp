#include<algorithm>
#include<queue>
#include<stdio.h>
#define R(x) x=read()
using namespace std;
const int N=2005;
int n,m;
double f[N][N];
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch<='0'&&ch>='9') 
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}
int s,t;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      if(i!=j) f[i][j]=0;
      else f[i][j]=1;
    for(int i=1;i<=m;i++)
    {
        int a,b;double c;
        scanf("%d%d%lf",&a,&b,&c);
        f[a][b]=f[b][a]=max(f[a][b],1-c/100);
    }
    scanf("%d%d",&s,&t);
    for(int k=1;k<=n;k++)
     for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
       f[i][j]=max(f[i][j],f[i][k]*f[k][j]);
    printf("%lf\n",100/f[s][t]);
    return 0;
}