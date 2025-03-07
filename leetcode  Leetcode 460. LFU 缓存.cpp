// set solution
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