// 递归
class Solution {
    public:
        unordered_map<Node*, Node*> M;
        Node* copyRandomList(Node* head) {
            if (!head)
                return NULL;
            if (!M.count(head)) {
                Node *newHead = new Node(head->val);
                M[head] = newHead;
                newHead->random = copyRandomList(head->random);
                newHead->next = copyRandomList(head->next);
            }
            return M[head];
        }
    };

// 三次遍历，空间复杂度O(1)
class Solution {
    public:
        Node* copyRandomList(Node* head) {
            if (!head)
                return head;
            // 建立拷贝节点，设置next
            for(Node* now = head; now; now = now->next->next) {
                Node *newNow = new Node(now->val);
                newNow->next = now->next;
                now->next = newNow;
            }
            for(Node *now = head; now; now = now->next->next) {
                Node *newNow = now->next;
                newNow->random = (now->random)?now->random->next:NULL;
            }
            // 取得答案
            Node *ans = head->next;
            for(Node *now = head; now; now = now->next) {
                Node *newNow = now->next;
                now->next = newNow->next;
                newNow->next = (newNow->next)?newNow->next->next:NULL;
            }
            return ans;
        }
    };

// 两次遍历，空间复杂度O(n)
class Solution {
    public:
        unordered_map<Node*, Node*> M;
        Node* copyRandomList(Node* head) {
            for(Node* now = head; now; now = now->next) {
                Node *newNode = new Node(now->val);
                M[now] = newNode;
            }
            for(Node *now = head, *newNow = M[head];now; now = now->next, newNow = newNow->next) {
                newNow->next = M[now->next];
                newNow->random = M[now->random];
            }
            return M[head];
        }
    };