# 其实r没有必要做离散化,浪费了性能
# 我们只需要压缩l的值域即可.
# 这个版本的离散化写得有问题，应该输入全部读完以后统一离散化，否则两个部分的输入值域不同，离散化结果也是错误的
import sys
import bisect

input = sys.stdin.readline

N = int(5e5 + 5)
M = int(1e9 + 5)

class TreeArr:
    def __init__(self, len):
        self.len = len
        self.arr = [0] * (len + 1)
    
    def update(self, pos, x):
        while (pos <= self.len):
            self.arr[pos] += x
            pos += (pos & (-pos))
    
    def query(self, pos):
        res = 0
        while pos:
            res += self.arr[pos]
            pos -= (pos & (-pos))
        return res


def main():
    n, m = tuple(map(int, input().strip().split()))
    origin_vals = []
    bacs: list[tuple] = []
    for _ in range(n):
        l, r = tuple(map(int, input().strip().split()))
        origin_vals.append(l)
        origin_vals.append(r)
        bacs.append((l, r))
    # 离散化
    vals = sorted(set(origin_vals))
    _max = len(vals)
    func = lambda x: bisect.bisect_left(vals, x) + 1
    for i in range(len(bacs)):
        bacs[i] = (func(bacs[i][0]), func(bacs[i][1]))
    bacs = sorted(bacs, key=lambda x: x[1])
    
    origin_vals.clear()

    # 记录查询
    queries = []
    for i in range(m):
        l, r = tuple(map(int, input().strip().split()))
        queries.append((i, l, r))
        origin_vals.append(l)
        origin_vals.append(r)
    
    # 离散化
    for i in range(len(queries)):
        queries[i] = (queries[i][0], func(queries[i][1]), func(queries[i][2]))

    queries = sorted(queries, key=lambda x: x[2])

    tree_arr =TreeArr(_max)
    idx = 0
    ans = [0] * m

    # 计算答案
    for i in range(m):
        qid, ql, qr = queries[i]
        while idx < len(bacs) and bacs[idx][1] <= qr:
            tree_arr.update(bacs[idx][0], 1)
            idx += 1
        ans[qid] = idx - tree_arr.query(ql - 1)
    
    print("\n".join(map(str, ans)))

if __name__ == "__main__":
    main()