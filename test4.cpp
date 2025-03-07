#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <set>
#include <string>
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
    Node(int k, int v, int f) : key(k), value(v), freq(f) {}
};
class LFUCache {
   public:
    LFUCache(int capacity) : _capacity(capacity) {}

    int get(int key) {
        auto find_res = key_table.find(key);
        if (find_res == key_table.end()) {
            return -1;
        }
        auto target = find_res->second;
        int value = target->value;
        reposition(target, value);
        return value;
    }

    void put(int key, int value) {
        auto find_res = key_table.find(key);
        if (find_res == key_table.end()) {
            try_remove();
            Node node = Node(key, value, 1);
            min_freq = 1;
            freq_table[1].push_front(node);
            key_table[key] = freq_table[1].begin();
        } else {
            reposition(find_res->second, value);
        }
    }

    void try_remove() {
        if (key_table.size() < _capacity) return;
        Node node = freq_table[min_freq].back();
        freq_table[min_freq].pop_back();
        key_table.erase(node.key);
        if (freq_table[min_freq].size() == 0)
            freq_table.erase(min_freq), min_freq++;
    }

    void reposition(std::list<Node>::iterator it, int value) {
        int key = it->key, freq = it->freq;
        freq_table[freq].erase(it);
        if (freq_table[freq].size() == 0) {
            if (freq == min_freq) min_freq++;
        }
        freq++;
        Node node = Node(key, value, freq);
        freq_table[freq].push_front(node);
        key_table[key] = freq_table[freq].begin();
    }

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

int main() {
    std::list<int> l(10, 2);
    auto it = l.begin();
    std::advance(it, 1);
    l.insert(it, 3);
    std::advance(it, -1);
    std::cout << *it << std::endl;
    return 0;
}
