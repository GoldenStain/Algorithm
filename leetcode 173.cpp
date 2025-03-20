// 预处理
class BSTIterator {
   public:
    BSTIterator(TreeNode *root) : _root(root), idx(0) { make_arr(arr, _root); }

    int next() { return arr[idx++]; }

    bool hasNext() { return idx < arr.size(); }

   private:
    TreeNode *_root;
    int idx;
    vector<int> arr;
    void make_arr(vector<int> &arr, TreeNode *root) {
        if (!root) {
            return;
        }
        make_arr(arr, root->left);
        arr.push_back(root->val);
        make_arr(arr, root->right);
    }
};

// 栈实时处理请求
class BSTIterator {
   public:
    BSTIterator(TreeNode *root) : _root(root) {}

    int next() {
        while (_root) {
            stk.push_back(_root);
            _root = _root->left;
        }
        _root = stk.back();
        stk.pop_back();  // 使用掉了
        int ans = _root->val;
        _root = _root->right;
        return ans;
    }

    bool hasNext() { return _root || stk.size(); }

   private:
    TreeNode *_root;
    vector<TreeNode *> stk;
};