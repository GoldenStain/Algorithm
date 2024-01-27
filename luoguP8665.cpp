#include <bits/stdc++.h>
using namespace std;

int get()
{
	int h1,m1,s1,h2,m2,s2,day=0;
	scanf("%d:%d:%d %d:%d:%d",&h1,&m1,&s1,&h2,&m2,&s2);
	if(getchar()==' ')scanf("(+%d)",&day);
	return (day*86400+h2*3600+m2*60+s2)-(h1*3600+m1*60+s1);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int ans=(get()+get())/2;
		printf("%02d:%02d:%02d\n",ans/3600,ans%3600/60,ans%60);
	}
	return 0;
}