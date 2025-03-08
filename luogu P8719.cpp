#include<bits/stdc++.h>
using namespace std;
// sum是全局的字母个数，cnt是临时的，用来在check函数中统计数量。
int V , len , now , cnt[27] , sum[27];
int get_max(int len){
    // 这个公式当中，加号前后的部分，各自会被对方计算一次，所以结果要除以二。
    return ((len - (len / 26 + 1)) * (len / 26 + 1) * (len % 26) + (26 - len % 26) * (len / 26) * (len - len / 26)) / 2;
}
bool check(int x , int n){
    memset(cnt , 0 , sizeof(cnt));
    int add1 = 0 , add2 = 0;
    for(int j = 26 ; j >= x + 1 ; j --) add1 += sum[j];
    sum[x] ++ ;//当前字符数量增加1
    // 逐个位置去尝试。
    for(int L = 1 ; L <= n ; L ++){
        // num表示的是：从1~i(这个i是主函数循环里的i)当中，能够和当前所用字母组成逆序对的字母个数
        // 之所以要倒序循环，也是为了保证他们能组成逆序对
        // 例如当前j到了字母x，那么num已经加过了sum[y] sum[z]，这些都是一定能产生逆序对的
        // 而cnt[j]则表示在放置当前字母之前，i+1~len当中，已经有的j字母的个数
        // 而从i+1~len，能产生的逆序对的最大数量，就是除j以外，其他字母的数量，也就是总数-已经有的-当前这个位置=L-cnt[j]-1
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
    // now表示已经确定的逆序对数量
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