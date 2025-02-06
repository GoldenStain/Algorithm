class Solution {
public:
    int hIndex(vector<int>& citations) {
        int h[1005], cnt = 0;
        memset(h, 0, sizeof(h));
        for(auto &ci : citations) {
            h[ci]++;
        }
        for (int i = 1; i <= 1000; i++) {
            h[i] += h[i - 1];
        }
        int l = 0, r = std::min(int(citations.size()), 1000);
        while(l < r) {
            int mid = (l + r + 1) >> 1;
            int t = mid == 0?h[1000]:h[1000]-h[mid - 1];
            if (t >= mid)
                l = mid;
            else 
                r = mid - 1;
        }
        return l;
    }
};

// wrong solution
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int h[1005], arr[1005], cnt = 0;
        memset(h, 0, sizeof(h));
        for(auto &ci : citations) {
            h[ci + 1]++;
        }
        for (int i = 1; i <= 1001; i++) {
            if (h[i])
                arr[++cnt] = i;
            h[i] += h[i - 1];
        }
        int l = 0, r = cnt;
        while(l < r) {
            int mid = (l + r + 1) >> 1;
            if (h[1001] - h[arr[mid] - 1] >= arr[mid] - 1)
                l = mid;
            else 
                r = mid - 1;
        }
        return arr[l] - 1;
    }
};