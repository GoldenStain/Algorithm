using PII = std::pair<int, int>;
using string = std::string;
template <typename T, typename Compare = std::less<T>>
class LazyHeadp
{
	std::priority_queue<T, std::vector<T>, Compare> pq;
	std::unordered_map<T, int> remove_cnt;
	size_t _size = 0;
	void try_remove()
	{
		while (!pq.empty() && remove_cnt[pq.top()] > 0)
		{
			remove_cnt[pq.top()]--;
			pq.pop();
		}
	}

   public:
	size_t size()
	{
		return _size;
	}

	void push(T x)
	{
		_size++;
		pq.push(x);
	}

	T top()
	{
		try_remove();
		return pq.top();
	}

	T pop()
	{
		try_remove();
		_size--;
		T x = pq.top();
		pq.pop();
		return x;
	}

	void remove(T x)
	{
		_size--;
		remove_cnt[x]++;
	}

	T push_pop(T x)
	{
		// 注意这里用_size,因为这才是真实的大小;不能用pq.size(),这时候还没进行矫正
		// 这里也不能直接用pq.top()，要用top()函数，这才是真实的top()
		// 如果x比堆顶更差，那么不知道会pop谁，需要实际执行一下
		if (_size && Compare()(x, top()))
		{
			pq.push(x);
			// 这里用pq.top()和top()是一样的，因为已经矫正过了
			x = pq.top();
			pq.pop();
		}
		// x比堆顶更好，就没必要操作了，push再pop就是X
		return x;
	}
};
class Solution
{
   public:
	vector<double> medianSlidingWindow(vector<int>& nums, int k)
	{
		int n = nums.size();
		std::vector<double> ans(n - k + 1);
		LazyHeadp<int> left;  // left是存储较小的一边，是大根堆
		LazyHeadp<int, std::greater<int>>
			right;	// right是存储较大的一边，是小根堆

		// 用i枚举右端点
		for (int i = 0; i < n; i++)
		{
			int in = nums[i];
			// 新元素入队
			if (left.size() == right.size())
			{
				left.push(right.push_pop(in));
			}
			else
			{
				right.push(left.push_pop(in));
			}
			int l = i - k + 1;
			if (l < 0)
				continue;
			// 更新答案
			if (k & 1)
			{
				ans[l] = left.top();
			}
			else
			{
				ans[l] = ((long long)left.top() + right.top()) / 2.0;
			}
			// 旧元素出队
			if (nums[l] <= left.top())
			{
				left.remove(nums[l]);
				// 堆的元素发生了变化，记得维护两个堆的平衡性
				if (left.size() < right.size())
					left.push(right.pop());
			}
			else
			{
				right.remove(nums[l]);
				if (left.size() > right.size() + 1)
					right.push(left.pop());
			}
		}
		return ans;
	}
};