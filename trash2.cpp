# include <iostream>
# include <array>
# include <algorithm>
# include <vector>

class Solution {
public:
    void nextPermutation(std::vector<int>& nums) {
		int i = nums.size() - 2;
		while(i >= 0 && nums[i] >= nums[i + 1])
			i--;
		if (i < 0) {
			std::reverse(nums.begin(), nums.end());
			return;
		}
		int j = nums.size() - 1;
		while(j >= 0 && nums[j] <= nums[i]) 
			j--;
		std::swap(nums[i], nums[j]);
		std::reverse(nums.begin() + i + 1, nums.end());
    }
};

int main() {
	Solution s;
	std::vector<int> nums{1,1,5};
	s.nextPermutation(nums);
	for(auto x: nums) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}