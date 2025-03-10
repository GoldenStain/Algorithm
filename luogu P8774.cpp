#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int P=998244353;
int n,a[N],b[N];
int fp(int x,int y){ // 快速幂
    int res=1;
    for(;y;y>>=1){
        if(y&1) res=(1ll*res*x)%P;
        x=(1ll*x*x)%P;
    }
    return res;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
    int s1=1,s2=0,s3=0;
    for(int i=1;i<=n;i++){ 
        int p1=(1ll*a[i]*fp(b[i],P-2))%P; //费马小定理求出概率
        int p2=(1ll*(b[i]-a[i])*fp(b[i],P-2))%P;
        s3=(s3+s1)%P; // 计算系数
        s2=(s2+1ll*s1*p1)%P;
        s1=(1ll*s1*p2)%P;
    }
    printf("%d",(1ll*s3*fp(1-s2+P,P-2))%P);
    return 0;
}