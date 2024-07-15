/*
 *  алгоритм Кнута-Морриса-Пратта для поиска по образцу
 */

#include <iostream>
#include <vector>
using namespace std;

//префикс-функция, которая выдает p{i} - такую наиб длину наибольшего собственного суффикса 
//(не совпадающ. со всей строкой) подстроки s[0 .. i], совпадающего с её префиксом
vector<int> getPrefixFunction(const string& s)
{
	int length = (int)s.length();
	vector<int> pi(length, 0);
	for (int i = 1; i < length; i++)
	{
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j])
		{
			j = pi[j - 1];
		}
		if (s[i] == s[j])
		{
			j++;
		}
		pi[i] = j;
	}
	return pi;
}

//реализация поиска
void getKMPSearch(const string& text, const string& substring)
{
	vector<int> pi = getPrefixFunction(substring + '#' + text);
	//определяем длину строки
	int tLength = (int)text.length();
	//с какого места ищем образец
	int sLen = (int)substring.length();
	//ищем образец
	for (int i = 0; i < tLength; i++)
	{
		if (pi[sLen + 1 + i] == sLen)
		{
			cout << i - sLen + 1 << ".." << i << "   ";
		}
	}
}

void printPrefix(const string& s)
{
	vector<int> pi = getPrefixFunction(s);
	cout << "Prefix function: ";
	for (auto elem : pi)
	{
		cout << elem << " ";
	}
	cout << "\n";
}

int main()
{
	string text, substring;
	cout << "Enter the text" << "\n";
	cin >> text;
	cout << "Enter the sub" << "\n";
	cin >> substring;
	printPrefix(text);
	cout << "Entrance '" << text << "' into '" << substring << "' : ";
	getKMPSearch(text, substring);

	return 0;
}


//abacaba
 //abcabcd