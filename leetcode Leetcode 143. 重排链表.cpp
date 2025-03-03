// 额外空间做法

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    public:
        void reorderList(ListNode* head) {
            std::vector<ListNode*> vec;
            for(;head;head = head->next) {
                vec.emplace_back(head);
            }
            int i = 0, j = vec.size() - 1;
            while(i < j) {
                vec[i]->next = vec[j];
                i++;
                if (i == j)
                    break;
                vec[j]->next = vec[i];
                j--;
            }
            vec[i]->next = nullptr;
        }
    };

// 常数空间做法

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    public:
        void reorderList(ListNode* head) {
            ListNode *middle_ptr = find_middle(head);
            ListNode *l2 = middle_ptr->next;
            middle_ptr->next = nullptr;
            l2 = reverseList(l2);
            connectList(head, l2);
        }
    
    private:
        ListNode *find_middle(ListNode *head) {
            ListNode *slow = head, *fast = head;
            while(fast && fast->next) {
                fast = fast->next->next;
                slow = slow->next;
            }
            return slow;
        }
    
        ListNode *reverseList(ListNode *head) {
            if (!head || !head->next)
                return head;
            ListNode *dummy = new ListNode(-1, head), *prev = nullptr;
            ListNode *_next;
            while(head) {
                _next = head->next;
                head->next = prev;
                prev = head;
                head = _next;
            }
            dummy->next = prev;
            return dummy->next;
        }
    
        void connectList(ListNode *l1, ListNode *l2) {
            ListNode *tmp1, *tmp2;
            while(l1 && l2) {
                tmp1 = l1->next;
                tmp2 = l2->next;
                l1->next = l2;
                l1 = tmp1;
                l2->next = l1;
                l2 = tmp2;
            }
        }
    };