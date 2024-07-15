/*
 * алгоритм Бойера-Мура для поиска по образцу
 */

#include <iostream>
#include <vector>
#include <map>
using namespace std;

//функция, проверяющая, содержится ли символ в строке
bool contains(const map<char, int>& m, char c)
{
	if (m.find(c) != m.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//функция получения таблицы сдвигов 
map<char, int> getShiftTable(string& s)
{
	map<char, int> table;
	//считаем длину подстроки
	int length = (int)s.length();
	table['*'] = length;
	//запускаем цикл, указываем наименьшую величину, на которую нужно сдвинуть вправо шаблон, чтобы он снова совпал со строкой
	for (int i = length - 2; -1 < i; i--)
	{
		//если сивол не содержится в строке
		if (!contains(table, s[i]))
		{
			table[s[i]] = length - i - 1;
		}
	}
	if (!contains(table, s[length - 1]))
	{
		table[s[length - 1]] = length;
	}
	return table;
}

void getBMSearch(string& text, string& substring)
{
	map<char, int> table = getShiftTable(substring);
	int tLength = (int)text.length();
	int sLength = (int)substring.length();
	int i = sLength - 1; //текущая позиция в тексте
	int j = sLength - 1;
	int lastI = i, offset; //смещение к text
	if (tLength < sLength)
	{
		cout << "образ не найден" << "\n";
	}
	while (i < tLength)
	{
		if (text[i] == substring[j])
		{
			i--;
			j--;
		}
		else if (i != lastI)
		{
			i = lastI + table[text[tLength - 1]];
			lastI = i;
			j = sLength - 1;
		}
		else
		{
			if (!contains(table, text[i]))
			{
				offset = table['*'];
			}
			else
			{
				offset = table[text[i]];
			}
			i = lastI + offset;
			lastI = i;
			j = sLength - 1;
		}
		if (j < 0)
		{
			cout << i + 1 << "\n";
			break;
		}
	}
}

void printTable(string& s)
{
	map<char, int> table = getShiftTable(s);
	cout << "table" << "\n";
	for (auto el : table)
	{
		cout << "[ " << el.first << " ] [ " << el.second << " ]" << "\n";
	}
}

int main()
{
	string text, substring;
	cout << "Enter the text" << "\n";
	cin >> text;
	cout << "Enter the sub" << "\n";
	cin >> substring;
	getBMSearch(text, substring);
	printTable(substring);
	return 0;
}

