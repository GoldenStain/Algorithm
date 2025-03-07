// set solution
struct Node {
    int key, value, time,
        freq;  // time表示最后一次使用的时间戳，用来对应"recently".
    Node() = default;
    Node(int k, int v, int t, int f = 1) : key(k), value(v), time(t), freq(f) {}
    bool operator<(const Node &other) const {
        return freq != other.freq ? freq < other.freq : time < other.time;
    }
};

class LFUCache {
   public:
    LFUCache(int capacity) : _capacity(capacity) {}

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
        } else {
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
        } else {
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

// list solution

struct Node {
    int key, value, freq;
    Node(int k, int v, int f) : key(k), value(v), freq(f) {}
};
class LFUCache {
   public:
    LFUCache(int capacity) : _capacity(capacity) {}

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
        } else {
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
        } else {
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
