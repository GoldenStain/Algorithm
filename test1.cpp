#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <valarray>
#include <vector>

class Solution {
public:
    int solve(std::vector<int> &arr) {
        int n = arr.size();
        int left = 0, right = n - 1;
        int ans = -1;
        while (left < right) {
            int minHeight = std::min(arr[left], arr[right]);
            ans = std::max((right - left)* minHeight, ans);
            if (minHeight == arr[left]) {
                left++;
            }
            else {
                right--;
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    std::vector<int> input = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    std::vector<int> input2 = {1, 1};
    std::cout << sol.solve(input2);
    return 0;
}
