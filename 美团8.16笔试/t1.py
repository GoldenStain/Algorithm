import sys

LENGTH = 30
UPPER = (1 << LENGTH) - 1

def len_of_bits(x):
    ans: int = 0
    while x:
        ans += 1
        x >>= 1
    if not ans:
        ans = 1
    return ans

def main():
    input = sys.stdin.read().strip('\r\n\t ').split()
    it = iter(input)
    T = int(next(it))
    ans = []
    for _ in range(T):
        n = int(next(it))
        arr = [int(next(it)) for _ in range(n)]
        s = sum(arr)
        _max = max(arr)
        len = len_of_bits(_max)
        mask = (1 << len) - 1
        upper = UPPER
        for ai in arr:
            upper &= ai
        upper &= mask
        x: int = mask ^ upper # 通过和mask异或，来翻转0和1
        s += x
        ans.append(f"{s} {x}")
    print("\n".join(ans))

if __name__ == "__main__":
    main()