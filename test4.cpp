#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <list>
#include <unordered_map>

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

struct Node {
    int key, value, freq;
    Node(int k, int v, int f): key(k), value(v), freq(f) {}
};
class LFUCache {
   public:
    
   private:
   // 这里的key_table键值要选择迭代器而不是Node本身，是因为我们没法通过Node本身去高效地访问一个std::list，就像我们手写的链表要用指针去访问一样，std::list要高效访问，就需要用到迭代器。
    std::unordered_map<int, std::list<Node>::iterator> key_table;
    std::unordered_map<int, std::list<Node>> freq_table;
    int _capacity, min_freq = 0;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() { return 0; }
