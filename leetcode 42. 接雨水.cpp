// DP
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        std::vector<int> lmax(n, 0), rmax(n, 0);
        lmax[0] = height[0];
        rmax[n - 1] = height[n - 1];
        for(int i = 1; i < n; i++)
            lmax[i] = std::max(lmax[i - 1], height[i]);
        for(int i = n - 2; i >= 0; i--)
            rmax[i] = std::max(rmax[i + 1], height[i]);
        int ans = 0;
        for(int i = 1; i < n - 1; i++)
            ans += std::min(lmax[i], rmax[i]) - height[i];
        return ans;
    }
};

// 单调栈
class Solution {
public:
    int trap(vector<int>& height) {
        int top = 0;
        int n = height.size();
        std::vector<int> stk(n+1);
        int ans = 0;
        for(int i = 0; i < height.size(); i++) {
            while(top && height[stk[top]] < height[i]) {
                int mid = height[stk[top--]];
                if(top == 0)
                    break;
                int left = stk[top];
                ans += (std::min(height[left], height[i]) - mid) * (i - left - 1);
            }
            stk[++top] = i;
        }
        return ans;
    }
};

// 双指针
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int leftMax = -1, rightMax = -1;
        int l = 0, r = n - 1;
        int ans = 0;
        while(l < r) {
            leftMax = std::max(leftMax, height[l]);
            rightMax = std::max(rightMax, height[r]);
            if (leftMax < rightMax)
                ans += leftMax - height[l++];
            else
                ans += rightMax - height[r--];
        }
        return ans;
    }
};

