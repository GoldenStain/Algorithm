import sys
import heapq

INF = 4*10**9
n: int = 0

def DJ(edges, stones, dist):
    q = []
    vis = [False] * (n+1)
    for i in range(1, n + 1):
        if dist[i] != INF:
            heapq.heappush(q, (dist[i], i))
    while len(q):
        dis, id = heapq.heappop(q)
        if vis[id]:
            continue
        vis[id] = True
        for v, w in edges[id]:
            new_dis = dis + stones[v] + w
            if new_dis < dist[v]:
                dist[v] = new_dis
                heapq.heappush(q, (dist[v], v))

def main():
    input = sys.stdin.read().strip().split()
    it = iter(input)
    global n
    n = int(next(it))
    m = int(next(it))
    k = int(next(it))
    # stones表示魔法石分数的真实值
    stones = [0] * (n + 1)
    # one_layer_stones表示只在单层图内跑时，魔法石的分数
    one_layer_stones = stones.copy()
    for i in range(1, n + 1):
        stones[i] = int(next(it))
        one_layer_stones[i] = max(stones[i], 0)
    # 连边，每个点用一个list存储边，用终点和边权表示一条边
    edges = [[] for _ in range(n + 1)]
    for _ in range(m):
        u = int(next(it))
        v = int(next(it))
        w = int(next(it))
        edges[u].append((v, w))
        edges[v].append((u, w))

    cur = [INF] * (n+1)
    cur[1] = 0
    nxt = []
    ans = INF
    # 在原图上跑一遍
    DJ(edges, one_layer_stones, cur)
    ans = min(ans, cur[n])

    # 在分层图上跑
    for _ in range(k):
        nxt = [INF] * (n+1)
        # 初始化距离
        for u in range(1, n + 1):
            if cur[u] >= INF:
                continue
            # 跨层连边
            for v, w in edges[u]:
                if stones[v] < 0:
                    new_dis = stones[v] + cur[u] + w
                    if new_dis < nxt[v]: # 注意这里是nxt，我们在更新nxt数组
                        nxt[v] = new_dis
        # 注意缩进，DJ应该是在这个level执行
        DJ(edges, one_layer_stones, nxt)
        ans = min(ans, nxt[n])
        cur = nxt
    if ans >= INF//2:
        print("NO")
    else:
        print(ans)

if __name__ == "__main__":
    main()