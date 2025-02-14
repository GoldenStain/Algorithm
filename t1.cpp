#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define For(i, j, n) for (int i = j; i <= n; ++i)
#ifdef DEBUG
#define DEBUG_LOG(fmt, ...)                  \
    do {                                     \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
    } while (0);
#else
#define DEBUG_LOG(fmt, ...) \
    do {                    \
    } while (0);
#endif

using VecInt = std::vector<int>;

template <typename T>
inline T read() {
    T x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

constexpr int Base = 100000, Cnt = 5;

struct CalculatedResult {
    VecInt Res;
    bool is_negative = false;
    int decimal = 0;
};

class Calculator {
   public:
    Calculator(std::string a) {
        // 倒叙存储数字
        int st = 0;
        while (st < a.size() && a[st] == '0') st++;
        if (st == a.size()) st--;
        for (int i = a.size() - 1, j = 0, sum = 0, t = 1; i >= st; i--) {
            sum = sum + (a[i] - '0') * t;
            t *= 10;
            j++;
            if (j == Cnt || i == st) {
                V.push_back(sum);
                j = 0;
                t = 1;
            }
        }
        len = V.size();
    }

    // 打印
    static void print(CalculatedResult &Res) {
        if (Res.is_negative)
            printf("-");
        printf("%d", Res.Res.back());
        for(int i = Res.Res.size() - 2; i >= Res.decimal; i--) {
            printf("%0*d", Cnt, Res.Res[i]);
        }
    }

    // 加法
    CalculatedResult operator+(Calculator &B) {
        int n = this->len, m = B.len;
        VecInt Res(std::max(n, m), 0);
        int t = 0;
        for(int i = 0; i < std::max(n, m) || t; i++) {
            int a = i < n ? V[i] : 0;
            int b = i < m ? B.V[i] : 0;
            t = t + a + b;
            Res[i] = t % Base;
            t /= Base;            
        }
        // 消除前导零
        return pack(removeLeadingZeros(Res), 0, 0);
    }

    // 减法
    VecInt operator-(Calculator &B) {

    }

   private:
    VecInt V;
    int len;
    VecInt removeLeadingZeros(VecInt &Res) {
        while(Res.size() > 1 && Res.back() == 0)
            Res.pop_back();
        return Res;
    }

    CalculatedResult pack(const VecInt &Res, bool sign, int decimal) {
        return CalculatedResult{Res, sign, decimal};
    }
};

int main() {
    std::string a, b;
    std::cin >> a >> b;
    Calculator A = Calculator(a), B = Calculator(b);
    CalculatedResult ans;
    // test add
    ans = A + B;
    Calculator::print(ans);
    // test minus
    ans = A - B;
    Calculator::print(ans);
    return 0;
}
