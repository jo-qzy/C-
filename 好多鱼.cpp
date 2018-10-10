//牛牛有一个鱼缸。鱼缸里面已经有n条鱼，每条鱼的大小为fishSize[i](1 ≤ i ≤ n, 均为正整数)
//牛牛现在想把新捕捉的鱼放入鱼缸。鱼缸内存在着大鱼吃小鱼的定律。
//经过观察，牛牛发现一条鱼A的大小为另外一条鱼B大小的2倍到10倍(包括2倍大小和10倍大小)，鱼A会吃掉鱼B。
//考虑到这个，牛牛要放入的鱼就需要保证：
//1、放进去的鱼是安全的，不会被其他鱼吃掉
//2、这条鱼放进去也不能吃掉其他鱼
//输入数据包括3行.第一行为新放入鱼的尺寸范围minSize, maxSize(1 ≤ minSize, maxSize ≤ 1000)，以空格分隔。
//第二行为鱼缸里面已经有鱼的数量n(1 ≤ n ≤ 50)
//第三行为已经有的鱼的大小fishSize[i](1 ≤ fishSize[i] ≤ 1000)，以空格分隔。

#include <iostream>
#include <set>
#include <string.h>

using namespace std;

int main()
{
	int minSize = 0, maxSize = 0;
	int n = 0;
	int size = 0;
	char hash[1000] = { 0 };
	set<int> check;
	while (cin >> minSize >> maxSize)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> size;
			if (hash[size] != 1)
			{
				int j = 0;
				hash[size] = 1;
				for (j = 2 * size; j <= 10 * size && j <= maxSize; j++)
					if (j >= minSize)
						check.insert(j);
				j = (size / 10 > minSize) ? (size / 10) : minSize;
				if (size > 10 && j == size / 10 && size % 10 != 0)
					j++;
				for (j; j <= size / 2 && j <= maxSize; j++)
					check.insert(j);
			}
		}
		cout << maxSize - minSize + 1 - check.size() << endl;
		check.clear();
		memset(hash, 0, 1000);
	}
	return 0;
}