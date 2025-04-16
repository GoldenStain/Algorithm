// 手写双向链表
struct BiListNode {
  int key, val;
  BiListNode *prev, *next;
  BiListNode(int key_ = -1, int val_ = -1, BiListNode *prev_ = nullptr,
             BiListNode *next_ = nullptr)
      : key(key_), val(val_), prev(prev_), next(next_) {}
};

class LRUCache {
public:
  LRUCache(int capacity) {
    dummy_fore->next = dummy_back;
    dummy_back->prev = dummy_fore;
    _capacity = capacity;
  }

  int get(int key) {
    if (M.count(key)) {
      BiListNode *ans = M[key];
      moveToHead(ans);
      return ans->val;
    } else {
      return -1;
    }
  }

  void put(int key, int value) {
    if (M.count(key)) {
      BiListNode *ans = M[key];
      ans->val = value;
      moveToHead(ans);
    } else {
      _size++;
      BiListNode *new_node = new BiListNode(key, value);
      M[key] = new_node;
      addHead(new_node);
      if (_size > _capacity) {
        BiListNode *tail = dummy_back->prev;
        // 注意删除的是键值相关的M记录，而不是val
        M.erase(tail->key);
        deleteBack();
        _size--;
        delete (tail);
      }
    }
  }

private:
  int _capacity, _size = 0;
  BiListNode *dummy_fore = new BiListNode(-1, -1),
             *dummy_back = new BiListNode(-1, -1);
  std::unordered_map<int, BiListNode *> M;
  void deleteNode(BiListNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void addHead(BiListNode *node) {
    dummy_fore->next->prev = node;
    node->next = dummy_fore->next;
    node->prev = dummy_fore;
    dummy_fore->next = node;
  }

  void moveToHead(BiListNode *node) {
    deleteNode(node);
    addHead(node);
  }

  void deleteBack() {
    BiListNode *node = dummy_back->prev;
    deleteNode(node);
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// 使用list实现
class LRUCache {
  using PII = std::pair<int, int>;

public:
  LRUCache(int capacity) : capacity_(capacity) {}

  int get(int key) {
    auto kv_pair = M.find(key);
    if (kv_pair == M.end()) {
      return -1;
    }
    auto link_node = kv_pair->second;
    int ans = link_node->second;
    replace_node(link_node, ans);
    M[key] = link_.begin();
    return ans;
  }

  void put(int key, int value) {
    auto kv_pair = M.find(key);
    if (kv_pair == M.end()) {
      link_.push_front({key, value});
      M[key] = link_.begin();
      if (size_ == capacity_)
        remove_old();
      else
        size_++;
    } else {
      replace_node(kv_pair->second, value);
      M[key] = link_.begin();
    }
  }

private:
  int capacity_ = 0, size_ = 0;
  unordered_map<int, list<PII>::iterator> M;
  list<PII> link_;
  void replace_node(list<PII>::iterator node, int value) {
    int key = node->first;
    link_.erase(node);
    link_.push_front({key, value});
  }
  void remove_old() {
    auto node = link_.back();
    int key = node.first;
    link_.pop_back();
    M.erase(key);
  }
};