#include<bits/stdc++.h>
using namespace std;
const int N=100100;
int a[N],n;
int get_pivot(int q[], int l, int r)
{
    int mid = l + r >> 1;
    if(q[r] > q[mid]) swap(q[r], q[mid]); // r <= mid
    if(q[l] < q[r]) swap(q[l], q[r]); // l >= r
    if(q[l] > q[mid]) swap(q[l], q[mid]); // l <= mid
    swap(q[l], q[r]); // 中位数在r
    return q[r];
}
void quick_sort(int q[], int l, int r)
{
    if(l >= r) return;
    int i = l, j = r;//注意是向上取整,因为向下取整可能使得x取到q[l]
    int x = get_pivot(q, l, r);
    cout << x << endl;
    while(i < j)
    {
        do i++; while(q[i] < x);
        do j--; while(q[j] > x);
        if(i < j) swap(q[i], q[j]);
    }
    swap(q[i], q[r]);
    for(int k = l; k <= r; k++)
        cout << a[k] << ' ';
    puts("");
    quick_sort(q, l, i - 1), quick_sort(q, i + 1, r);//不用q[l..i],q[i+1..r]划分的道理和分析4中j的情况一样
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    quick_sort(a,1,n);
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    system("pause");
    return 0;
}