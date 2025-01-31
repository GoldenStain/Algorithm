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
#include <vector>
#include <unordered_map>
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        int i = 0;
        ListNode *new_origin = new ListNode(0, head);
        head = new_origin;
        ListNode *start = head;
        while(head) {
            if (i)
                sum[i] = sum[i - 1] + head->val;
            else
                sum[i] = head->val;
            m[sum[i]] = head;
            i++;
            head = head->next;
        }
        ListNode *new_start = start;
        i = 0;
        while(start) {
            if (i)
                new_sum[i] = new_sum[i - 1] + start->val;
            else
                new_sum[i] = start->val;
            if (m.find(new_sum[i]) != m.end() && m[new_sum[i]] != start) {
                start->next = m[new_sum[i]]->next;
            }
            i++;
            start = start->next;
        }
        return new_start->next;
    }
private:
    int sum[1005], new_sum[1005];
    std::unordered_map<int, ListNode*> m;
};