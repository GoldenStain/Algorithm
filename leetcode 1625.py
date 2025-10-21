import math
class Solution:
    def findLexSmallestString(self, s: str, a: int, b: int) -> str:
        s = list(map(int, s))
        n = len(s)
        g = math.gcd(a, 10)
        ans = [math.inf] 
        step = math.gcd(n, b)
        def modify(t, idx: int):
            num = t[idx]
            # target: num % g
            changed = (num % g - num + 10) % 10
            if changed:
                for j in range(idx, n, 2):
                    t[j] = (t[j] + changed) % 10
        for i in range(0, n, step):
            tmp = s[i:] + s[:i]
            modify(tmp, 1)
            if step % 2 != 0:
                modify(tmp, 0)
            if not ans or ans > tmp:
                ans = tmp
        return "".join(map(str, ans))