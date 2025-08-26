// POJ 2352 Stars
#include <algorithm>
#include <array>
#include <cstdio>
#include <iterator>
#include <random>
#include <vector>

constexpr int N = 1e5 + 5, M = 1e9 + 5;
using PII = std::pair<int, int>;
std::vector<int> origin_vals;
std::vector<PII> bacs;
std::vector<std::tuple<int, int, int>> queries;

int n, m;

inline int lowbit(int x) {
    return x & (-x);
}

struct TreeArr {
    int len;
    std::vector<int> arr;
    TreeArr(int l): len(l) {
        arr.resize(len + 1, 0);
    }

    void update(int pos, int x) {
        while (pos <= len) {
            arr[pos] += x;
            pos += lowbit(pos);
        }
    }

    int query(int pos) {
        int res = 0;
        while (pos) {
            res += arr[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
};

inline int mapping(std::vector<int> &a, int x) {
    return (std::lower_bound(a.begin(), a.end(), x) - a.begin()) + 1;
}

int main() {
    std::freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    int l, r;

    bacs.resize(n);
    queries.resize(m);

    for (int i = 0; i < n; i++) {
        scanf("%d%d", &l, &r);
        origin_vals.push_back(l);
        bacs[i] = {l, r};
    }

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &l ,&r);
        origin_vals.push_back(l);
        queries[i] = std::tuple{r, l, i};
    }
    // 离散化
    std::sort(origin_vals.begin(), origin_vals.end());
    origin_vals.erase(std::unique(origin_vals.begin(), origin_vals.end()), origin_vals.end());
    for (int i = 0; i < n; i++) {
        bacs[i].first = mapping(origin_vals, bacs[i].first);
    }
    for (int i = 0; i < m; i++) {
        std::get<1>(queries[i]) = mapping(origin_vals, std::get<1>(queries[i]));
    }
    auto func = [](PII a, PII b)->bool {return a.second < b.second;};

    std::sort(bacs.begin(), bacs.end(), func);
    std::sort(queries.begin(), queries.end());

    auto tree_arr = TreeArr(origin_vals.size());
    int idx = 0;
    std::vector<int> ans(m, 0);
    for (int i = 0; i < m; i++) {
        while (idx < n && bacs[idx].second <= std::get<0>(queries[i])) {
            tree_arr.update(bacs[idx].first, 1);
            idx++;
        }
        int t = std::get<2>(queries[i]);
        ans[t] = idx - tree_arr.query(std::get<1>(queries[i]) - 1);
    }
    for (int i = 0; i < m; i++) 
        printf("%d\n", ans[i]);
    return 0;
}