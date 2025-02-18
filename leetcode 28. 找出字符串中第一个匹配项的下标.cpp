class Solution {
    public:
        int strStr(string haystack, string needle) {
            int n = haystack.size(), m = needle.size();
            std::vector<int> nxt(m);
            nxt[0] = -1;
            for(int i = 1, j = -1; i < m; i++) {
                while(~j && needle[j + 1] != needle[i])
                    j = nxt[j];
                if (needle[j + 1] == needle[i])
                    j++;
                nxt[i] = j;
            }
            for(int i = 0, j = -1; i < n; i++) {
                while(~j && needle[j + 1] != haystack[i])
                    j = nxt[j];
                if (needle[j + 1] == haystack[i])
                    j++;
                if (j == m - 1)
                    return i - j;
            }
            return -1;
        }
    };