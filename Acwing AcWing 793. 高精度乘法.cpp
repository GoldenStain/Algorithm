#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

#define For(i, j, n) for(int i = j ; i <= n ; ++i)
#ifdef DEBUG
#define DEBUG_LOG(fmt, ...)                  \
do {                  \
\
fprintf(stderr, fmt, ##__VA_ARGS__); \
} while (0);
#else
#define DEBUG_LOG(fmt, ...) \
do {                    \
} while (0);
#endif

using VecInt = std::vector<int>;
constexpr int Base = 100000, Cnt = 5;

template <typename T>
inline T read()
{
    T x = 0;
    int f = 1; char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
       x = x * 10 + ch - '0';
       ch = getchar();
    }
    return x * f;
}

void Input(VecInt &X, std::string &x) {
    int st = 0;
    while(st < x.size() && x[st] == '0')
        st++;
    for(int i = x.size() - 1, sum = 0, j = 0, t = 1; i >= st; i--) {
        sum = sum + (x[i] - '0') * t;
        t *= 10;
        j++;
        if (j == Cnt || i == st) {
            X.push_back(sum);
            sum = 0;
            t = 1;
            j = 0;
        }
    }
}

VecInt mul(VecInt &A, int b) {
    int t = 0;
    for(int i = 0; i < A.size() || t; i++) {
        if (i < A.size())
            t += A[i] * b;
        if (i >= A.size())
            A.emplace_back(0);
        A[i] = t % Base;
        t /= Base;
    }
    while(A.size() > 1 && A.back() == 0)
        A.pop_back();
    return A;
}

VecInt superMul(VecInt &A, VecInt &B) {
    int sa = A.size(), sb = B.size();
    VecInt C(sa + sb, 0);
    for(int i = 0; i < sa; i++) {
        for(int j = 0; j < sb; j++) {
            C[i + j] += A[i] * B[j];
            C[i + j + 1] += C[i + j] / Base;
            C[i + j] %= Base;
        }
    }
    while(C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}

int main()
{
    std::string a, b;
    int *num_b = nullptr;
    VecInt A;
    std::cin >> a >> b;
    Input(A, a);
    if (b.size() <= 5)
        num_b = new int (std::stoi(b));
    // super
    if (!num_b) {
        VecInt B;
        Input(B, b);
        A = superMul(A,B);
    }
    // normal
    else {
        A = mul(A, *num_b);
    }
    delete num_b;
    printf("%d", A[A.size() - 1]);
    for(int i = A.size() - 2; i >= 0; i--)
        printf("%0*d", Cnt, A[i]);
    return 0;
}
