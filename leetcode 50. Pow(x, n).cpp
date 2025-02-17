class Solution {
    public:
        double myPow(double x, int n) {
            if (n < 0)
                return 1/(_pow(x, -(n+1)) * x);
            return _pow(x, n);
        }
        double _pow(double x, int n) {
            double ans = 1;
            while(n) {
                if (n & 1)
                    ans *= x;
                x *= x;
                n >>= 1;
            }
            return ans;
        }
    };