import sys, math

def select_primes(upper, flags, primes: list):
    for i in range(2, upper):
        if not flags[i]:
            primes.append(i)
        for pj in primes:
            if pj > upper // i:
                break
            flags[pj * i] = True
            if i % pj == 0:
                break

def resolve(x, primes):
    res = []
    for pi in primes:
        if x % pi == 0:
            res.append(pi)
            while x % pi == 0:
                x //= pi
    # 记得不要漏掉x本身是质数的情况
    if x > 1:
        res.append(x)
    return res

def read_int():
    with open('input.txt', 'r', encoding='utf-8') as file:
        data = file.read().strip().split()
        for i in data:
            yield int(i)

def main():
    it = iter(read_int())
    n = next(it, 0)
    print(n)
    
    freqs = {}
    _max = 0
    # 没必要获取全部的输入，只要拿到>1的那部分就行了
    for _ in range(n):
        num = next(it)
        if num <= 1:
            continue
        freqs[num] = freqs.get(num, 0) + 1
        _max = max(_max, num)

    if len(freqs.keys()) == 0:
        print("0 0")
        sys.exit(0)

    # 筛质数
    upper = math.isqrt(_max) + 1
    prime_flag = [False] * (upper + 1)
    primes: list[int] = []
    select_primes(upper, prime_flag, primes)

    # 分解质因数，求最大长度
    cover = {} # 每个质数能覆盖几个元素
    base = {} # 每个质数覆盖的元素组当中，各个元素的gcd是多少
    for n, t in freqs.items():
        for pi in resolve(n, primes):
            cover[pi] = cover.get(pi, 0) + t
            base[pi] = n if pi not in base else math.gcd(base[pi], n)

    ans = max(cover.values(), default=1)
    if ans == 1:
        print(f"1 {len(freqs)}")
        sys.exit(0)

    # 统计答案
    seen = set()
    cnt = 0
    candidates = [pi for pi in cover if cover[pi] == ans]
    for pi in candidates:
        if pi in seen:
            continue
        for qi in resolve(base[pi], primes):
            seen.add(qi)
        cnt += 1
    
    print(f"{ans} {cnt}")



if __name__ == "__main__":
    main()