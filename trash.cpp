

### 数学原理详解

**问题模型**：  
有 $ n $ 个有序选项（如楼层、应聘者），依次观察并决策。每次只能选择当前选项或放弃（不可回溯），目标最大化选到最大值的概率。

**最优策略推导**：

1. **策略定义**：  
   观察前 $ k $ 个选项，记录最大值 $ M $。之后，一旦遇到比 $ M $ 大的选项，立即选择。若后续无更大值，则被迫选最后一个。

2. **成功条件**：  
   设最大选项位于位置 $ i $（$ 1 \leq i \leq n $）。策略成功需满足：
   - $ i > k $（最大值在决策阶段）。
   - 前 $ i-1 $ 个选项中，最大值在前 $ k $ 个中（否则在位置 $ i $ 前已被选中）。

3. **概率计算**：  
   - 最大值出现在位置 $ i $ 的概率：$ \frac{1}{n} $（均匀分布）。
   - 最大值在前 $ k $ 中的条件概率：若 $ i > k $，则前 $ i-1 $ 个中的最大值必须在前 $ k $ 个中，概率为 $ \frac{k}{i-1} $。

   总成功概率：
   $$
   P(k) = \sum_{i=k+1}^n \frac{1}{n} \cdot \frac{k}{i-1} = \frac{k}{n} \sum_{i=k}^{n-1} \frac{1}{i}
   $$

4. **近似与优化**：  
   当 $ n $ 很大时，求和近似为积分：
   $$
   \sum_{i=k}^{n-1} \frac{1}{i} \approx \int_{k}^{n} \frac{1}{x} dx = \ln\left(\frac{n}{k}\right)
   $$
   因此：
   $$
   P(k) \approx \frac{k}{n} \ln\left(\frac{n}{k}\right)
   $$
   令 $ x = \frac{k}{n} $，则：
   $$
   P(x) \approx x \ln\left(\frac{1}{x}\right)
   $$
   对 $ x $ 求导并令导数为零：
   $$
   \frac{dP}{dx} = \ln\left(\frac{1}{x}\right) - 1 = 0 \implies x = \frac{1}{e}
   $$
   即最优 $ k \approx \frac{n}{e} $，对应观察前约 37% 的选项。

**结论**：  
- **最优停止点**：前 37% 作为观察期，之后选择首个更优者。
- **成功概率**：约 $ \frac{1}{e} \approx 36.8\% $，为理论最大值。
- **应用场景**：招聘、投资、租房等需实时决策且不可回溯的问题。

**公式总结**：  
$$
\boxed{k = \frac{n}{e}, \quad P_{\text{max}} = \frac{1}{e}}
$$
此策略平衡了“探索”与“利用”，以数学极限确保最大概率捕获最优解。