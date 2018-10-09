#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	bool checkSeq(string& s)
	{
		char check[26][5] = { 0 };//标记每个重复字母所在位置
		vector<int> flag;//标记哪几个字母有重复的
		auto cur = s.begin();
		while (cur != s.end())
		{
			if (cur[0] < 'A' || cur[0] > 'Z')
				return false;//如果有不是大写字母的，返回错误
			if (cur + 1 != s.end() && cur[0] == cur[1])
				return false;//如果前后相同的，返回错误
			if (check[cur[0] - 'A'][4] < 4)
			{
				check[cur[0] - 'A'][check[cur[0] - 'A'][4]] = cur - tmp.begin();
				if (++check[cur[0] - 'A'][4] == 4)
					return false;
				if (check[cur[0] - 'A'][4] == 2)
					flag.push_back(cur[0] - 'A');
			}
			//hash[cur[0] - 'A'] = 1;
			cur++;
		}
		if (tmp.size() >= 4)
		{
			//子序列长度大于4才有判断的意义
			//查找是否有XYXY型的子串
			//只有有字母Y处于两个X之间，另一个Y处于X的后面的位置，那么就是XYXY
			for (int i = 0; i < flag.size(); i++)
			{
				for (int j = 1; j < flag.size(); j++)
				{
					if (check[flag[j]][0] > check[flag[i]][0] && check[flag[j]][0] < check[flag[i]][1])
						if ((check[flag[j]][1] > check[flag[i]][1]) || (check[j][4] > 2 && check[flag[j]][1] > check[flag[i]][2]))
							return false;
					if (check[j][4] > 2 && check[flag[j]][0] > check[flag[i]][1] && check[flag[j]][0] < check[flag[i]][2])
						if (check[flag[j]][1] > check[flag[i]][2] || check[flag[j]][1])
							return false;
				}
			}
		}
		return true;
	}
};

int main()
{
	string s;
	Solution solve;
	while (cin >> s)
	{
		if (solve.checkSeq(s))
			cout << "Likes" << endl;
		else
			cout << "Dislikes" << endl;
	}
	return 0;
}