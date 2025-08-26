#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
constexpr int N = 2e6 + 5, M = 2e8 + 5;
int P = static_cast<int>(std::sqrt(M));

std::unordered_map<int, int> freqs, cover, base;
std::vector<int> primes, factors;
int n;

inline void select_primes(int upper) {
    std::vector<char> flag (upper + 1, 0);
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

void resolve(int x) {
    factors.clear();
    for (auto pi: primes) {
        if (x % pi == 0) {
            factors.push_back(pi);
            while (x % pi == 0) {
                x /= pi;
            }
        }
    }
    if (x != 1) {
        factors.push_back(x);
    }
}

int gcd(int x, int y) {
    if (!y) {
        return x;
    }
    return gcd(y, x%y);
}

int main() {
    std::freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // 没必要获取全部输入，只要>1的
    int x, _max = 0;
    std::cin >> n;
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
        resolve(key);
        for (auto ai: factors) {
            cover[ai] += pi.second;
            if (base.find(ai) == base.end()) {
                base[ai] = pi.first;
            } else {
                base[ai] = gcd(base[ai], pi.first);
            }
        }
    }
    for (auto &pi: cover) {
        L = std::max(L, pi.second);
    }
    if (L == 1) {
        std::cout << L << " " << freqs.size() << std::endl;
        return 0;
    }
    std::unordered_set<int> seen;
    int ans = 0;
    // 注意这里是cover而不是primes
    for (auto &pi: cover) {
        if (seen.contains(pi.first)) 
            continue;
        if (cover[pi.first] < L) {
            continue;
        }
        resolve(base[pi.first]);
        for (auto &vi: factors) {
            seen.insert(vi);
        }
        ans++;
    }
    std::cout << L << " " << ans << std::endl;
    return 0;
}