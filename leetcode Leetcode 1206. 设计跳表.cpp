constexpr double P = 0.5;
constexpr int MAX_LEVEL = 16;
struct SkipNode {
    int val;
    vector<SkipNode*> list;
    SkipNode(int _val, int _max_level = MAX_LEVEL)
        : val(_val), list(_max_level, nullptr) {}
};

class Skiplist {
   public:
    Skiplist() : head(new SkipNode(-1)), level(0) {}

    bool search(int target) {
        SkipNode *cur = this->head;
        // 从上往下找
        for(int i = level - 1; i >= 0; i--) {
            while(cur->list[i] && cur->list[i]->val < target)
                cur = cur->list[i];
        }
        cur = cur->list[0];
        // 要小心访问到空地址
        return cur && cur->val == target;
    }

    void add(int num) {
        // 这里要开MAX_LEVEL个，因为后面的新level可能会超过现有的level
        std::vector<SkipNode*> update(MAX_LEVEL, head);
        SkipNode *cur = this->head;
        for(int i = level - 1; i >= 0; i--) {
            while(cur->list[i] && cur->list[i]->val < num)
                cur = cur->list[i];
            // 用update记录每层最后一个被访问的节点
            update[i] = cur;
        }
        SkipNode *_insert = new SkipNode(num);
        int lv = gen_lv();
        // 更新层数
        level = std::max(level, lv);
        // 新节点插入在update[i]的后面
        for(int i = 0; i < lv; i++) {
            _insert->list[i] = update[i]->list[i];
            update[i]->list[i] = _insert;
        }
    }

    bool erase(int num) {
        // 这里只要开level个，因为在这个函数level只会变小不会变大
        std::vector<SkipNode*> update(level, head);
        // 跟erase一模一样
        SkipNode *cur = head;
        for(int i = level - 1; i >= 0; i--) {
            while(cur->list[i] && cur->list[i]->val < num)
                cur = cur->list[i];
            // 用update记录每层最后一个被访问的节点
            update[i] = cur;
        }
        // 我们没必要记录cur的prev，因为update已经发挥了这个作用
        cur = cur->list[0];
        if (!cur || cur->val != num)
            return false;
        // 要先完成连接的修改再delete掉cur，不然会空悬指针
        for(int i = 0; i < level; i++) {
            // 如果cur在这一层没有出现，那么再往上它都不会出现了
            if (update[i]->list[i] != cur)
                break;
            update[i]->list[i] = cur->list[i];
        }
        // 可以安全地删除cur了
        delete cur;
        // 更新层数
        while(level > 1 && head->list[level - 1] == nullptr)
            level--;
        return true;
    }
    
   private:
    SkipNode* head;
    int level;
    // 注意，生成引擎不是用device对象来初始化的，使用device对象的调用结果来初始化的
    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    int gen_lv() {
        // level初始化为0是因为一开始整个跳表是空的，所以我们的层数相当于0，但是add操作是一定会加入实际节点的，那么它的层数就应该至少是1
        int res = 1;
        // 分布器传入的是引擎对象
        while(dis(gen) <= P && res < MAX_LEVEL) 
            res++;
        return res;
    }
};