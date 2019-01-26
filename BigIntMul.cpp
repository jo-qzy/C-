#include <iostream>
#include <string>

using namespace std;

string addNum(string& num1, string& num2) {
	if (num1.size() < num2.size())
		swap(num1, num2);
	string ret;
	bool flag = false;
	auto it1 = num1.rbegin(), it2 = num2.rbegin();
	while (it2 != num2.rend()) {
		char ch = *it1 - '0' + *it2;
		if (flag == true) {
			ch += 1;
			flag = false;
		}
		if (ch > '9') {
			ch = ch - 10;
			flag = true;
		}
		ret += ch;
		it1++, it2++;
	}
	while (it1 != num1.rend()) {
		char ch = *it1;
		if (flag == true) {
			ch += 1;
			flag = false;
			if (ch > '9') {
				flag = true;
				ch -= 10;
			}
		}
		ret += ch;
		it1++;
	}
	if (flag == true)
		ret += '1';
	return string(ret.rbegin(), ret.rend());
}

string mulNum(string& num1, string& num2) {
	if (num1.size() < num2.size())
		swap(num1, num2);
	auto it = num2.rbegin();
	string ret;
	for (int i = 0; i < num2.size(); i++) {
		string tmp_num;
		if (*it == '1')
			tmp_num = num1;
		else {
			for (auto e : num1) {
				char tmp = (*it - '0') * (e - '0');
				char carry = 0;
				if (tmp > 9) {
					carry += tmp / 10;
					tmp = tmp % 10 + '0';
					if (tmp_num.size() != 0) {
						carry += '0';
						string c;
						carry_str += carry;
						tmp_num = addNum(tmp_num, carry_str);
					}
					else
						tmp_num += (carry + '0');
				}
				else
					tmp += '0';
				tmp_num += tmp;
			}
		}
		for (int i = 0; i < it - num2.rbegin(); i++)
			tmp_num += '0';
		ret = addNum(ret, tmp_num);
		it++;
	}
	return ret;
}

int main()
{
	string num1, num2;
	cin >> num1 >> num2;
	cout << mulNum(num1, num2) << endl;
	return 0;
}