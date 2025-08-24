#include <iostream>
#include <cstring>
#include <istream>
#include <array>

constexpr int N = 1e5;
int P;

std::array<int, N + 1> w;

struct SegTree{
    // lazy tag的含义：当前子树（除去该节点本身）所需要做的修改.
    int l, r, sum, mul, add;
};
std::array<SegTree, N << 2> seg_tree;
int n, m;

inline void push_up(int u) {
    seg_tree[u].sum = (seg_tree[u << 1].sum + seg_tree[u<<1|1].sum)%P;
}

// u:线段树节点编号，l&r:当前节点的区间范围
void build(int u, int l, int r) {
    if (l == r) {
        seg_tree[u] = {l, r, w[l], 1, 0};
        return;
    }
    seg_tree[u] = {l, r, 0, 1, 0};
    int mid = (l + r) >> 1;
    // 二分当中，划分区间的标准是:每次变动，区间必须和上次不同，否则可能死循环
    // 这里也是同理
    build(u<<1, l, mid);
    build(u<<1|1, mid + 1, r);
    push_up(u);
}

// 这个eval更贴切的名字应该是modify，但是modify已经被占用了，所以这里用eval，这个函数本质上既有eval的操作，也有modify的操作
void eval(SegTree& t, int mul, int add) {
    t.sum = (static_cast<long long>(t.sum) * mul % P + static_cast<long long>(t.r - t.l + 1) * add) % P;
    t.mul = static_cast<long long>(t.mul) * mul % P;
    t.add = (static_cast<long long>(t.add) * mul % P + add) % P;
}

inline void push_down(int u) {
    auto& t = seg_tree[u];
    eval(seg_tree[u<<1], t.mul, t.add);
    eval(seg_tree[u<<1|1], t.mul, t.add);
    t.mul = 1;t.add = 0;
}

// u:当前节点的编号;l&r:这次操作所要修改的范围;mul:这次引入的乘法标记;add:这次引入的加法标记
void modify(int u, int l, int r, int mul, int add) {
    auto& t = seg_tree[u];
    if (t.l >= l && t.r <= r) {
        eval(t, mul, add);
        return;
    }
    int mid = (t.l + t.r) >> 1;
    push_down(u);
    if (l <= mid) {
        modify(u<<1, l, r, mul, add);
    }
    if (r > mid) {
        modify(u<<1|1, l, r, mul, add);
    }
    push_up(u);
}

// 同modify
int query(int u, int l, int r) {
    auto &t = seg_tree[u];
    if (t.l >= l && t.r <= r) {
        return t.sum;
    }
    int mid = (t.l + t.r) >> 1;
    push_down(u);
    int res = 0;
    if (l <= mid) {
        res = query(u<<1, l, r);
    }
    if (r > mid) {
        res = (res + query(u<<1|1, l, r)) % P;
    }
    return res;
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> P;
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i];
    }
    
    build(1, 1, n);

    int op, l, r, val;
    std::cin >> m;

    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op <= 2) {
            std::cin >> l >> r >> val;
            if (op == 1) {
                modify(1, l, r, val, 0);
            }
            else {
                modify(1,  l,  r, 1, val);
            }
        }
        else {
            std::cin >> l >> r;
            std::cout << query(1, l, r) << "\n";
        }
    }
    return 0;
}