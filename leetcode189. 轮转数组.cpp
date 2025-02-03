// solution 1
class Solution {
   public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        vector<int> tmp(nums.size() * 2, 0);
        for (int i = 0; i < 2 * n; i++) {
            tmp[i] = nums[i % n];
        }
        nums.clear();
        for (int i = 0, s = n - k; i < n; i++, s++) nums.push_back(tmp[s]);
    }
};

// solution 2
class Solution {
   public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        if (!k) return;
        vector<int> tmp = nums;
        for (int i = 0, s = n - k; i < n; i++) {
            nums[i] = tmp[s];
            s = (s + 1) % n;
        }
    }
};

// solution 3
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        _reverse(nums, 0, n) ;
        _reverse(nums, 0, k);
        _reverse(nums, k, n);
    }
private:
    void _reverse(vector<int>& nums, int l, int r) {
        int i = l, j = r - 1;
        while(i < j) {
            std::swap(nums[i], nums[j]);
            i++;
            j--;
        }
    }
};

// solution 4
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        int cnt = gcd(n, k);
        for(int i = 0; i < cnt; i++) {
            int prev = nums[i], cur = i;
            do {
                cur = (cur + k) % n;
                std::cout << cur << " " << nums[cur] << std::endl;
                std::swap(nums[cur], prev);
            } while(cur != i);
        }
    }
private:
    int gcd(int a, int b) {
        if(!b)
            return a;
        return gcd(b, a%b);
    }
};

// wrong solution 4
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        int cnt = gcd(n, k);
        for(int i = 0; i < cnt; i++) {
            int prev = nums[i], cur = (i + k)%n;
            do {
                std::swap(nums[cur], prev);
                cur = (cur + k) % n;
            } while(cur != i);
        }
    }
private:
    int gcd(int a, int b) {
        if(!b)
            return a;
        return gcd(b, a%b);
    }
};