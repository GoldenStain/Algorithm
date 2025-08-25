#include <cmath>
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <unordered_map>
constexpr int N = 2e6 + 5, M = 2e8 + 5;
int P = static_cast<int>(std::sqrt(M));

std::unordered_map<int, int> freqs;
std::vector<int> primes, factors;
int n;

inline void select_primes(int upper) {
    std::vector<char> flag (P, 0);
    for (int i = 2; i <= upper; i++) {
        if (!flag[i])
            primes.emplace_back(i);
        for (int j = 0; j < primes.size() && primes[j] <= upper / i; j++) {
            flag[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // 没必要获取全部输入，只要>1的
    int x, _max;
    for (int i = 1; i <= n; i++) {
        std::cin >> x;
        if (x <= 1)
            continue;
        freqs[x]++;
        _max = std::max(_max, x);
    }
    if(freqs.empty()) {
        std::cout << "0 0";
        return 0;
    }
    int upper = static_cast<int>(std::sqrt(_max)) + 1;
    // 筛质数
    select_primes(upper);
    // 统计长度
    int L = 0;
    for (auto &pi: freqs) {
        int key = pi.first;
        
    }
    return 0;
}