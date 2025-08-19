import sys
import bisect

def low_bit(x):
    return x & (-x)

class TreeArr:
    def __init__(self, upper):
        self.arr = [0] * (upper + 1)
        self.upper = upper

    def add(self, pos, val):
        now = pos
        while (now <= self.upper):
            self.arr[now] += val
            now += low_bit(now)

    def sum(self, pos):
        now = pos
        res = 0
        while now:
            res += self.arr[now]
            now -= low_bit(now)
        return res

def main():
    input = sys.stdin.read().strip().split()
    it = iter(input)
    n = int(next(it))
    a = [0] * (n + 1)
    for i in range(1, n + 1):
        a[i] = int(next(it))
    # 离散化
    vals = sorted(set(a))
    _max = len(vals)
    func = lambda x: bisect.bisect_left(vals, x) + 1 
    arr = [func(v) for v in a] # 注意这里是a，不是vals，把a里面大的值域映射到小的值域

    ans = 0
    # 我右边，小于等我的个数，用来计算a_j >= a_k
    less_or_equal_right = [0] * (n + 1)
    # 我左边，大于我的个数，用来计算a_i>a_j
    # 因为树状数组只能向下统计，所以这个greater_left需要通过一个减法间接得到
    # 不需要真的创建出来，可以在第二个循环逐步使用
    # greater_left = [0] * (n + 1)

    # 从后往前遍历
    backward_ta = TreeArr(_max)
    for i in range(n, 0, -1):
        cnt = backward_ta.sum(arr[i] - 1)
        less_or_equal_right[i] = backward_ta.sum(arr[i])
        ans += cnt * (cnt - 1) // 2 # 即组合数C(n, 2)
        backward_ta.add(arr[i], 1)
    
    # 然后从前往后
    forward_ta = TreeArr(_max)
    for i in range(1, n + 1, 1):
        cnt = i - 1 - forward_ta.sum(arr[i])
        ans -= cnt * less_or_equal_right[i]
        forward_ta.add(arr[i], 1)

    print(ans)


if __name__ == "__main__":
    main()
