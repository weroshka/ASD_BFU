//﻿Решить задачу о суммах подмножеств, используя жадный алгоритм

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> set = { 5, -7, 7, 3, -4 };
	vector<int> resultSet;
	int sum = set[0];
	resultSet.push_back(set[0]);

	for (int i = 1; i < set.size(); i++)
	{
		if (abs(sum + set[i]) < abs(sum))
		{
			sum += set[i];
			resultSet.push_back(set[i]);
		}
	}
	for (auto s : resultSet)
	{
		cout << s << " ";
	}
}