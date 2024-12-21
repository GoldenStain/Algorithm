#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <random>
#include <vector>
#define DEBUG
#define For(i, j, n) for (int i = j; i <= n; ++i)
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...)       \
	do                              \
	{                               \
		printf(fmt, ##__VA_ARGS__); \
	} while (0)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

template <typename T>
inline T read()
{
	T x = 0;
	int f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

class Solution
{
public:
	void sortColors(std::vector<int> &nums)
	{
		int m = nums.size();
		int zero_ptr = 0, two_ptr = m - 1;
		for (int i = 0; i < m && i <= two_ptr; i++)
		{
			if (nums[i] == 2 && i <= two_ptr)
				std::swap(nums[i], nums[two_ptr--]);
			if (!nums[i])
				std::swap(nums[i], nums[zero_ptr++]);
		}
	}
};

class localExperiment
{
public:
	void sort01(std::vector<int> &nums)
	{
		int zero_ptr = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (!nums[i])
				std::swap(nums[i], nums[zero_ptr++]);
		}
		for (auto num : nums)
			std::cout << num << " ";
		std::cout << std::endl;
	}
};

// 模板的 T 参数表示元素的类型，此类型需要定义小于（<）运算
template <typename T>
// arr 为需要被排序的数组，len 为数组长度
void quick_sort(T arr[], const int len)
{
	if (len <= 1)
		return;
	// 随机选择基准（pivot）
	const T pivot = 1;
	// i：当前操作的元素下标
	// arr[0, j)：存储小于 pivot 的元素
	// arr[k, len)：存储大于 pivot 的元素
	int i = 0, j = 0, k = len;
	// 完成一趟三路快排，将序列分为：
	// 小于 pivot 的元素 | 等于 pivot 的元素 | 大于 pivot 的元素
	while (i < k)
	{
		for(int i = 0; i < len; i++)
			printf("%d ", arr[i]);
		printf("\n");
		printf("%d %d %d\n", j, i, k);
		if (arr[i] < pivot)
			std::swap(arr[i++], arr[j++]);
		else if (pivot < arr[i])
			std::swap(arr[i], arr[--k]);
		else
			i++;
	}
	// 递归完成对于两个子序列的快速排序
	// quick_sort(arr, j);
	// quick_sort(arr + k, len - k);
}

int main()
{
	int seed = 114514;
	srand(seed);
	std::vector<int> a;
	// for(int i = 0; i < 10; i++)
	// 	a.push_back(rand() % 3);

	int nums[20] = {0, 2, 0, 1, 0, 2, 1, 2};
	quick_sort(nums, 8);
	for(int i = 0; i < 8; i++)
		printf("%d ", nums[i]);
	
	a = {0, 2, 0, 1, 0, 2, 1, 2};
	for (int &ai : a)
		std::cout << ai << " ";
	std::cout << std::endl;
	localExperiment le;
	Solution s;
	s.sortColors(a);
	for (int &ai : a)
		std::cout << ai << " ";
	return 0;
}
