// wrong solution, from end to begin.
class Solution {
    public:
     vector<string> fullJustify(vector<string>& words, int maxWidth) {
         int n = words.size(), len = words[n - 1].size();
         vector<string> ans;
         int st = n - 1;
         for (int i = n - 2; i >= 0; i--) {
             if (len + words[i].size() + 1 <= maxWidth)
                 len += words[i].size() + 1;
             else {
                 st = i + 1;
                 break;
             }
         }
         if (len != maxWidth)
             st = n - 1;
         std::string tmp = words[st];
         for (int i = st + 1; i < n; i++) tmp += " " + words[i];
         if (tmp.size() < maxWidth) tmp.append(maxWidth - tmp.size(), ' ');
         ans.emplace_back(tmp);
 
         for (int i = st - 1; i >= 0; i--) {
             int j = i;
             len = words[i].size();
             for (j = i - 1; j >= 0; j--) {
                 if (len + words[j].size() + 1 <= maxWidth)
                     len += words[j].size() + 1;
                 else {
                     break;
                 }
             }
             j++;
             int cnt = i - j, diff = maxWidth - len, quo = -1, r = -1;
             // cnt有可能是0，这一行只有一个单词
             if (cnt) {
                 quo = diff / cnt;
                 r = diff % cnt;
             }
             std::string tmp = words[j];
             if (quo == -1) tmp.append(maxWidth - len, ' ');
             for (int k = j + 1; k <= i; k++) {
                 tmp.append(quo + 1, ' ');
                 if (r) {
                     tmp.append(1, ' ');
                     r--;
                 }
                 tmp += words[k];
             }
             ans.emplace_back(tmp);
             i = j;
         }
         // finally
         reverse(ans.begin(), ans.end());
         return ans;
     }
 };

// true solution, from begin to the end.
