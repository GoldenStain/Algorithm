#include <bits/stdc++.h>
using namespace std;
int gcd(int m, int n)
{
	if(n)
	{
		return gcd(n, m % n);
	}
	else
	{
		return m;
	}
}//��gcd(m,n),�����ĵݹ�д��
const int MAXN = 105, MAX_DP = 100005;//��������
int n, a[MAXN], dp[MAX_DP], ans;
bool notCoprime(int *arr)//����arr�����������������Լ���Ƿ����1
{
	int g = arr[0];
	for(int i = 1; i < n; i++)
	{
		g = gcd(g, arr[i]);
		if(g == 1)
		{
			return false;//���g�Ѿ�Ϊ1��������ѭ����ֱ�ӷ���
		}
	}
	return g > 1;
}//���庯�������и���
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}//����
	if(notCoprime(a))//���gcd({A_i})>1
	{
		printf("INF");
		return 0;//ֱ�ӽ���
	}
	dp[0] = 1;//ע��0�Ǳ���Ϊ�ܱ��ճ��ģ��������������ղ�������ѭ�����ʱ���Բ��ô�0��ʼ
	for(int i = 0; i < n; i++)
	{
		for(int j = a[i]; j < MAX_DP; j++)
		{
			dp[j] = max(dp[j], dp[j - a[i]]);//״̬ת�Ʒ���
		}
	}
	for(int i = 1; i < MAX_DP; i++)
	{
		if(!dp[i])
		{
			ans++;//���dp[i]=0,��һ���ղ�������
		}
	}
	printf("%d", ans);//���
	return 0;
}