// O(n) BFS
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
   public:
    Node* connect(Node* root) {
        if (!root) return root;
        std::queue<Node*> q;
        q.push(root);
        while (q.size()) {
            int n = q.size();
            Node* prev = NULL;
            for (int i = 1; i <= n; i++) {
                Node* now = q.front();
                q.pop();
                if (i > 1) prev->next = now;
                if (now->left) q.push(now->left);
                if (now->right) q.push(now->right);
                prev = now;
            }
        }
        return root;
    }
};

// DFS
class Solution {
   public:
    Node* connect(Node* root) {
        if (!root) return root;
        dfs(root, 0);
        return root;
    }

   private:
    std::vector<Node*> arr;
    void dfs(Node* node, int depth) {
        if (depth == arr.size())
            arr.push_back(node);
        else {
            arr[depth]->next = node;
            arr[depth] = node;
        }
        if (node->left) dfs(node->left, depth + 1);
        if (node->right) dfs(node->right, depth + 1);
    }
};

// 压缩空间BFS

class Solution {
   public:
    Node* connect(Node* root) {
        if (!root) return root;
        // next_start表示下一层要从哪里开始，也就是下一层最左边的节点。
        Node* start = root;
        while (start) {
            Node* cur = start;
            // 这两个变量是以层为单位的，每一层都要重置。
            Node *prev = NULL, *next_start = NULL;
            while (cur) {
                if (cur->left) {
                    if (prev) prev->next = cur->left;
                    prev = cur->left;
                    if (!next_start) next_start = cur->left;
                }
                if (cur->right) {
                    if (prev) prev->next = cur->right;
                    prev = cur->right;
                    if (!next_start) next_start = cur->right;
                }
                cur = cur->next;
            }
            start = next_start;
        }
        return root;
    }
};