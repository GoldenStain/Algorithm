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

// 逆向思维
// f[k, m] k个蛋，m次能确定的最大楼层
// 未知数里面没有楼层，假设我们在任意一层扔了第一个蛋
// 如果没碎，那么下面最多有f[k, m - 1]层
// 碎了，那么上面最多有f[k - 1, m - 1]层
// 所以一共是1 + f[k, m - 1] + f[k - 1][m - 1]

// wrong Solution
// 这道题的可能数据范围非常大，就算是long
// long也存不下，我们如果把k放在第一维，那么要一直算到最后才可能出结果，就会在中途爆long
// long 另一方面，这也会导致退出循环的时间较晚，在时间上也不占优势
// 所以我们可以交换第一维和第二维，避免这个问题
class Solution {
   public:
    int superEggDrop(int k, int n) {
        vector<vector<long long>> f(k + 1, vector<long long>(n + 1, 0));
        for (int i = 1; i <= n; i++) {
            // 有可能只有一个蛋
            f[1][i] = i;
            if (f[k][i] >= n) return i;
        }
        for (int i = 2; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = f[i - 1][j - 1] + f[i][j - 1] + 1;
                if (f[k][j] >= n) {
                    // 题目问的是次数，这里的次数就是j
                    return j;
                }
            }
        }
        return 0;
    }
};

// true solution
class Solution {
   public:
    int superEggDrop(int k, int n) {
        vector<vector<long long>> f(n + 1, vector<long long>(k + 1, 0));
        for (int i = 1; i <= n; i++) {
            f[i][1] = i;
            // 这里不需要像wrong
            // Solution那样加特判，因为后面的f[i][k]会覆盖这种这种可能
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 2; j <= k; j++) {
                f[i][j] = 1 + f[i - 1][j] + f[i - 1][j - 1];
            }
            // 要放在第二层循环的外面，不然在k=1的时候不会覆盖到答案。
            if (f[i][k] >= n) {
                return i;
            }
        }
        return 0;
    }
};