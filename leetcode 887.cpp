class Solution {
   public:
    int superEggDrop(int k, int n) {
        vector<vector<int>> f(k + 1, vector<int>(n + 1, 0));
        // 注意边界条件一定要初始化好，不然的话初始的case都会偏小，导致后面所有的case都偏小
        // 这道题只需要初始化鸡蛋的边界情况，楼层不用；不过不放心且懒得证明的话，可以两个都初始化一下。
        for (int i = 1; i <= n; i++) f[1][i] = i;
        for (int i = 2; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = 1 + getF(f, i, j);
            }
        }
        return f[k][n];
    }
    int getF(vector<vector<int>>& f, int k, int x) {
        // 注意这个函数内部的“总楼层”应该是等于我们传入的j，而不是实际的最大楼层n
        // 推公式的时候用的是字母n，结果导致函数参数传递错误，debug了半天。
        int l = 1, r = x;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (f[k - 1][mid - 1] < f[k][x - mid])
                l = mid;
            else
                r = mid - 1;
        }
        int res = std::max(f[k - 1][l - 1], f[k][x - l]);
        if (x - l)  // 这个下标可能会越界，所以要判断一下
        {
            res = std::min(res, std::max(f[k - 1][l], f[k][x - l - 1]));
        }
        return res;
    }
};

// solution 2
class Solution {
   public:
    int superEggDrop(int k, int n) {
        vector<vector<int>> f(2, vector<int>(n + 1, 0));
        // 要先给idx赋值为1，如果鸡蛋只有1个的话，那这里的idx就作为最终输出了
        int idx = 1;
        for (int i = 1; i <= n; i++) f[1][i] = i;
        for (int i = 2; i <= k; i++) {  // 鸡蛋
            int point = 1;
            idx = i & 1;
            f[idx][1] = 1;
            for (int j = 2; j <= n; j++) {  // 层数
                while (point < j && f[idx ^ 1][point - 1] < f[idx][j - point])
                    point++;
                f[idx][j] =
                    std::max(f[idx ^ 1][point - 1], f[idx][j - point]) + 1;
            }
        }
        return f[idx][n];
    }
};