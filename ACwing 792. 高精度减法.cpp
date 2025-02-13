#include <iostream>
#include <vector>
#include <cstring>
using vecInt = std::vector<int>;

constexpr int Base = 1000000000, Cnt = 9;

void Input(vecInt &X, std::string &x) {
    int st = 0;
    // 处理前导零
    while(st < x.size() && x[st] == '0')
        st++;
    for(int i = x.size() - 1, sum = 0, t = 1, j = 0; i >= st; i--) {        
        sum = sum + (x[i] - '0') * t;
        t *= 10;
        j++;
        if (j == Cnt || i == st) {
            X.push_back(sum);
            sum=0;j=0;t=1;
        }
    }
}

bool cmp(vecInt &A, vecInt &B) {
    if (A.size() != B.size())
        return A.size() > B.size();
    // 要注意这里反转过了，所以高位在后面.
    for(int i = A.size() - 1; i >= 0; i--)
        if (A[i] != B[i])
            return A[i] > B[i];
    return true;
}

vecInt sub(vecInt &A, vecInt &B) {
    int t = 0;
    for(int i = 0; i < A.size(); i++) {
        int b = i < B.size() ? B[i] : 0;
        t = A[i] - t - b;
        A[i] = (t + Base) % Base;
        t = t >=0 ? 0: 1;
    }
    return A;
}

int main() {
    std::string a, b;
    std::cin >> a >> b;
    vecInt A, B;
    Input(A, a);
    Input(B, b);
    if (cmp(A, B))
        A = sub(A, B);
    else {
        printf("-");
        A = sub(B, A);
    }
    // 处理前导零，要注意记得加上这个size()的判断，如果整个结果里面只剩下一个0，说明结果真的就是0，不能再pop了.
    while(A.size() && A.back() == 0)
        A.pop_back();
    printf("%d", A[A.size() - 1]);
    for(int i = A.size() - 2; i >= 0; i--)
        printf("%09d", A[i]);
}