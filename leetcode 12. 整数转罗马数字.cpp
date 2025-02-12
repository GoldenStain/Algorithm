class Solution {
    public:
        string intToRoman(int num) {
            std::unordered_map<int, char> M;
            M[1] = 'I';M[5] = 'V';
            M[10] = 'X'; M[50] = 'L';
            M[100] = 'C'; M[500] = 'D';
            M[1000] = 'M';
            std::vector<int> keys = {1, 5, 10, 50, 100, 500, 1000};
            std::string snum = std::to_string(num), ans = "";
            int len = snum.size();
            int base = std::pow(10, len - 1);
            for (int i = 0; i < len; i++) {
                int n = snum[i] - '0';
                int val = n * base;
                if (n == 4 || n == 9) {
                    int bigger = *std::lower_bound(keys.begin(), keys.end(), val);
                    int smaller = bigger - val;
                    ans = ans + M[smaller] + M[bigger];
                }
                else {
                    while(val) {
                        int smaller = *(std::upper_bound(keys.begin(), keys.end(), val) - 1);
                        // std::cout << smaller << " " << val << std::endl;
                        ans += M[smaller];
                        val -= smaller;
                    }
                }
                base /= 10;
            }
            return ans;
        }
    };