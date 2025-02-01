
// solution 1
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (!m) {
            nums1 = nums2;
            return;
        }
        if (!n) {
            return;
        }
        std::vector<int> new_num = nums1;
        int i, j, k = 0;
        for(i = 0, j = 0;i < m && j < n;) {
            if (new_num[i] <= nums2[j])
                nums1[k++] = new_num[i++];
            else
                nums1[k++] = nums2[j++];
        }
        while(i < m)    
            nums1[k++] = new_num[i ++];
        while(j < n)
            nums1[k++] = nums2[j++];
    }
};

// solution 2
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j=n-1, k = m + n - 1;
        while(i>=0 && j>=0) {
            if (nums1[i] >= nums2[j])
                nums1[k--] = nums1[i--];
            else
                nums1[k--] = nums2[j--];
        }
        while(i>=0)
            nums1[k--] = nums1[i--];
        while(j>=0)
            nums1[k--] = nums2[j--];
    }
};
