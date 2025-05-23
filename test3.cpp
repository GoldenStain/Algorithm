#include<bits/stdc++.h>
using namespace std;
int V , len , now , cnt[27] , sum[27];
int get_max(int len){
    return ((len - (len / 26 + 1)) * (len / 26 + 1) * (len % 26) + (26 - len % 26) * (len / 26) * (len - len / 26)) / 2;
}
bool check(int x , int n){
    memset(cnt , 0 , sizeof(cnt));//cnt记录后面n个位置放置的对应字符数量
    int add1 = 0 , add2 = 0;
    for(int j = 26 ; j >= x + 1 ; j --) add1 += sum[j];//1~pos-1里边比当前插入字符大的字符数量
    sum[x] ++ ;//当前字符数量增加1
    for(int L = 1 ; L <= n ; L ++){
        //ma保存最大逆序对个数 L-1-cnt[j]+num
        //L-1-cnt[j]是当前字符之后的比当前字符小的字符数量的最大值
        //num是1~pos+L-1前的比当前放置字符字典序大的字符数量
        int ma = -1 , pos = 0 , num = 0;
        for(int j = 26 ; j >= 1 ; j --){
            if(L - 1 - cnt[j] + num > ma){
                ma = L - 1 - cnt[j] + num;
                pos = j;
            }
            num += sum[j];
        }
        add2 += ma , cnt[pos] ++;
    }
    if(now + add1 + add2 >= V) {
        now += add1;
        return true;
    }
    else {
        sum[x] -- ;
        return false;
    }
}
signed main()
{
    string ans = "";
    cin >> V;
    for(int i = 1 ; ; i ++) {
        if(get_max(i) >= V){
            len = i;
            break ;
        }
    }
    for(int i = 1 ; i <= len ; i ++){
        for(int j = 1 ; j <= 26 ; j ++){
            if(check(j , len - i)){
                ans += char(j + 'a' - 1);
                break ;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}