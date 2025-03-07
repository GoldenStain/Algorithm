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
    LFUCache(int capacity): _capacity(capacity) {}

    void reposition(std::list<Node>::iterator it, int value) {
        int freq = it->freq, key = it->key;
        freq_table[freq].erase(it);
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (freq == min_freq) min_freq++;
        }
        freq++;
        // 这里的操作用到了map的性质，如果[]内部索引的对应元素不存在，那么会先调用默认构造函数创建一个临时对象
        freq_table[freq].push_front(Node{key, value, freq});
        key_table[key] = freq_table[freq].begin();
    }

    void removeOld() {
        auto node = freq_table[min_freq].back();
        freq_table[min_freq].pop_back();
        int key = node.key, freq = node.freq;
        key_table.erase(key);
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (freq == min_freq) min_freq++;
        }
    }

    int get(int key) {
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            return -1;
        }
        else {
            auto iter = it->second;
            int value = iter->value;
            reposition(iter, value);
            return value;
        }
    }

    void put(int key, int value) {
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            Node node = Node(key, value, 1);
            if (key_table.size() == _capacity) {
                removeOld();
            }
            min_freq = 1;
            // 这里的操作用到了map的性质，如果[]内部索引的对应元素不存在，那么会先调用默认构造函数创建一个临时对象
            freq_table[1].push_front(node);
            key_table[key] = freq_table[1].begin();
        }
        else {
            auto iter = it->second;
            reposition(iter, value);
        }
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

int main() { return 0; }
