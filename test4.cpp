#include <stdio.h>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

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
    int key, value, time,
        freq;  // time表示最后一次使用的时间戳，用来对应"recently".
    Node() = default;
    Node(int k, int v, int t, int f = 1) : key(k), value(v), time(t), freq(f) {}
    bool operator < (const Node &other) const{
        return freq != other.freq ? freq < other.freq : time < other.time;
    }
};

class LFUCache {
   public:
    LFUCache(int capacity): _capacity(capacity) {}

    void reposition(Node &node, int v) {
        auto it = S.find(node);
        node.value = v;
        node.time = ++_time;
        node.freq++;
        S.erase(it);
        S.insert(node);
    }

    void discard() {
        Node removed = *S.begin();
        M.erase(removed.key);
        S.erase(S.begin());
    }

    int get(int key) {
        auto it = M.find(key);
        if (it == M.end()) {
            return -1;
        }
        else {
            int value = it->second.value;
            reposition(it->second, value);
            return value;
        }
    }

    void put(int key, int value) {
        auto it = M.find(key);
        if (it == M.end()) {
            Node new_node = Node(key, value, ++_time, 1);
            if (S.size() == _capacity) {
                discard();
            }
            M.insert({key, new_node});
            S.insert(new_node);
        } 
        else {
            reposition(it->second, value);
        }
    }
   private:
    int _capacity, _time = 0;
    std::set<Node> S;
    std::unordered_map<int, Node> M;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() { return 0; }
