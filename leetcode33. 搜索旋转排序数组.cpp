class Solution {
public:
  int search(vector<int> &nums, int target) {
    // 序列分两段递增
    int l = 0, r = nums.size() - 1;
    // 这里没有等号，所以最后需要多做一步判断
    while (l < r) {
      int mid = (l + r) >> 1;
      if (nums[mid] == target)
        return mid;
      // 如果比nums[0]大，那就在第一段，而因为mid =
      // l+r>>1，所以，只有l有可能等于 nums[0].
      // 也可以理解成，nums[0]本身是左半边的数字
      if (nums[mid] >= nums[0]) {
        // 如果小于nums[mid]也小于nums[0]，那就在右半段了
        if (target >= nums[0] && target < nums[mid]) {
          r = mid - 1;
        } else
          l = mid + 1;
      }
      // 右半段
      else {
        if (target <= nums[nums.size() - 1] && target > nums[mid])
          l = mid + 1;
        else
          r = mid - 1;
      }
    }
    // 如果在循环过程中没有直接找到也不能直接return
    // -1，可能最后一步才找到，这时候l==r，循环已经退出了。
    return (nums[l] == target) ? l : -1;
  }
};

// solution 2
// 更好的注释，更好的理解
class Solution {
public:
  int search(vector<int> &nums, int target) {
    int n = nums.size();
    int l = 0, r = n - 1;
    int loc = -1;
    // 这里有等号，所以最后不需要再做额外的判断了
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (nums[mid] == target) {
        loc = mid;
        break;
      }
      // mid is on the left
      if (nums[mid] >= nums[0]) {
        // we must make sure target is also on the left when we go left.
        if (nums[mid] > target && target >= nums[0]) {
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      // mid is on the right
      else {
        // the same as above
        if (nums[mid] < target && target < nums[0]) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
    }
    return loc;
  }
};