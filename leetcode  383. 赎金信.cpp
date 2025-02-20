// slow way
class Solution {
   public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> M;
        for (auto ci : magazine) M[ci]++;
        for (auto ci : ransomNote) {
            M[ci]--;
            if (M[ci] < 0) return false;
        }
        return true;
    }
};

// fast way

class Solution {
   public:
    bool canConstruct(string ransomNote, string magazine) {
        int cnt[26] = {0};
        for (int i = 0; i < magazine.size(); i++) cnt[magazine[i] - 'a']++;
        for (int i = 0; i < ransomNote.size(); i++) {
            int c = ransomNote[i] - 'a';
            cnt[c]--;
            if (cnt[c] < 0) return false;
        }
        return true;
    }
};