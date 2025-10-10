# 错解
class Solution:
    def maximumEnergy(self, energy: List[int], k: int) -> int:
        n = len(energy)
        ans = -1
        for i in range(n - 1 - k, -1, -1):
            energy[i] += energy[i + k]
            ans = max(ans, energy[i])
        return ans
# 错误原因：答案有可能出在enery[n - k, n - 1]之间，这种做法会错过这部分解

# 正解
class Solution:
    def maximumEnergy(self, energy: List[int], k: int) -> int:
        n = len(energy)
        ans = -1
        for i in range(n - 1 - k, -1, -1):
            energy[i] += energy[i + k]
        return max(energy)
