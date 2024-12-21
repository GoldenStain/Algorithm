#include <iostream>
#include <vector>

// O(n)遍历做法
// class Solution {
// public:
//     double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
// 		int lens = nums1.size() + nums2.size();
// 		int end_point = lens/2 + 1;
// 		int ans = 0;
// 		int t1 = INT_MAX, t2 = INT_MAX;
// 		// now_count已添加的个数
// 		for(int i = 0, j = 0, now_count = 0; now_count < end_point;)
// 		{
// 			// if(i < nums1.size() && nums1[i] <= nums2[j])
// 			// {
// 			// 	t1 = nums1[i];
// 			// 	i++;
// 			// }
// 			// else if(j < nums2.size())
// 			// {
// 			// 	t1 = nums2[j];
// 			// 	j++;
// 			// }
// 			if(i < nums1.size() && j < nums2.size())
// 			{
// 				if(nums1[i] <= nums2[j])
// 					t1 = nums1[i++];
// 				else 
// 					t1 = nums2[j++];
// 			}
// 			else
// 			{
// 				if(i < nums1.size())
// 					t1 = nums1[i++];
// 				else
// 					t1 = nums2[j++];
// 			}
// 			now_count++;
// 			if(now_count == end_point - 1 && now_count > 0)
// 			{
// 				ans = ans + t1;
// 				t2 = t1;
// 			}
// 			else if(now_count == end_point)
// 				ans = ans + t1;
// 		}
// 		if((end_point << 1) - lens == 1)
// 		{
// 			if(t2 != INT_MAX)
// 				ans = ans - t2;
// 			return ans;
// 		}
// 		else
// 			return (double)ans/2;
//     }
// };

// 类二分做法
// class Solution
// {
// public:
// 	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
// 	{
// 		// 保证nums1是较短的数组
// 		if(nums1.size() > nums2.size())
// 			return findMedianSortedArrays(nums2, nums1);
// 		int m = nums1.size(), n = nums2.size();
// 		if(m + n & 1)
// 			return findKthInArray(nums1, nums2, (m + n)/2 + 1);
// 		else
// 			return ((double)findKthInArray(nums1, nums2, (m + n)/2) + findKthInArray(nums1, nums2, (m + n)/2 + 1))/2;
// 	}
// 	int findKthInArray(vector<int>& nums1, vector<int>& nums2, int k)
// 	{
// 		// 边界情况

// 		// 递归过程

// 	}
// };

// 二分做法
// class Solution
// {
// public:
// 	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
// 	{
// 		// 保证nums1是较短的数组
// 		if(nums1.size() > nums2.size())
// 			return findMedianSortedArrays(nums2, nums1);
// 		int m = nums1.size(), n = nums2.size();
// 		int l = -1, r = m - 1;
// 		int cnt = (m + n + 1)/2; // cnt是个数, 向上取整
// 		int nums1_less, nums1_more, nums2_less, nums2_more;
// 		while(l <= r)
// 		{
// 			int mid = l + r >> 1, mid2 = cnt - mid - 2; // mid是下标，cnt - (mid + 1)算出来是个数，再减一转换成下标mid2
// 			nums1_less = (mid < 0) ? INT_MIN : nums1[mid];
// 			nums1_more = (mid + 1 < m) ? nums1[mid + 1] : INT_MAX;
// 			nums2_less = (mid2 < 0 || !n) ? INT_MIN : nums2[mid2];
// 			nums2_more = (mid2 + 1 < n) ? nums2[mid2 + 1] : INT_MAX;
// 			// cout << mid << " " << mid2 << endl;
// 			if(nums1_less <= nums2_more && nums1_more >= nums2_less)
// 			{
// 				// cout << mid << " " << mid2 << endl;
// 				if(m + n & 1) // 奇数
// 					return max(nums1_less, nums2_less);
// 				else
// 					return ((double)max(nums1_less, nums2_less) + min(nums1_more, nums2_more)) / 2;
// 			}
// 			else if(nums1_less < nums2_less)
// 				l = mid + 1;
// 			else	
// 				r = mid - 1;
// 		}
// 		return 233333;
// 	}
// };

// 伪二分做法
class Solution
{
public:
	double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
	{
		int m = nums1.size(), n =nums2.size();
		if(m > n)
			return findMedianSortedArrays(nums2, nums1);
		int total_nums = m + n;
		if(total_nums & 1)
			return find_kth_in_array(nums1, nums2, total_nums/2 + 1);
		else
			return (find_kth_in_array(nums1, nums2, total_nums/2) + find_kth_in_array(nums1, nums2, total_nums/2 + 1)) / 2;
	}
	double find_kth_in_array(std::vector<int>& nums1, std::vector<int>& nums2, int k)
	{
		int idx1 = 0, idx2 = 0;
		int m = nums1.size(), n = nums2.size();
		while(true)
		{
			if(idx1 >= m)
				return nums2[idx2 + k - 1];
			if(idx2 >= n)
				return nums1[idx1 + k - 1];
			if(k == 1)
			{
				return std::min(nums1[idx1], nums2[idx2]);
			}
			int k1 = k/2, k2 = k - k1;
			int new_idx1 = std::min(m - 1, idx1 + k1 - 1), new_idx2 = std::min(n - 1, idx2 + k2 - 1);
			int p1 = nums1[new_idx1], p2 = nums2[new_idx2];
			if(p1 <= p2)
			{
				k -= new_idx1 - idx1 + 1;
				idx1 = new_idx1 + 1;
			}
			else
			{
				k -= new_idx2 - idx2 + 1;
				idx2 = new_idx2 + 1;
			}
		}
	}
};

int main()
{
	std::vector<int> nums1 = {1, 3};
	std::vector<int> nums2 = {2};
	Solution s;
	std::cout << s.findMedianSortedArrays(nums1, nums2);
}