// my solution
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
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            ListNode *ans = l1, *prev1 = nullptr, *prev2 = nullptr;
            int carry = 0;
            while(l1 && l2) {
                l1->val += l2->val + carry;
                carry = l1->val / 10;
                l1->val %= 10;
                prev1 = l1;
                prev2 = l2;
                l1 = l1->next;
                l2 = l2->next;
            }
            if (l2)
                prev1->next = l2;
            l1 = prev1->next;
            while(carry) {
                if (!l1)
                    l1 = new ListNode(0, nullptr), prev1->next = l1;
                l1->val += carry;
                carry = l1->val/10;
                l1->val %= 10;
                prev1 = l1;
                l1 = l1->next;
            }
            return ans;
        }
    };

//最简便的写法
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
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            ListNode *dummy = new ListNode(), *cur = dummy;
            int carry = 0;
            while(l1 || l2 || carry) {
                int a = l1?l1->val:0;
                int b = l2?l2->val:0;
                int sum = a + b + carry;
                carry = sum >= 10 ? 1 : 0;
                cur->next = new ListNode(sum % 10);
                cur = cur->next;
                l1 = l1?l1->next:l1;
                l2 = l2?l2->next:l2;
            }
            return dummy->next;
        }
    };