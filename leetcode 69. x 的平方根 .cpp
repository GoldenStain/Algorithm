class Solution {
public:
    int mySqrt(int x) {
        int l = 0, r = x;
        while(l < r) {
            int mid = ((long long) (l) + r + 1) >> 1;
            if (x/mid >= mid)
                l = mid;
            else 
                r = mid - 1;
        }
        return l;
    }
};