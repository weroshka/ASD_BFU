/*
 * алгоритм Рабина для поиска по образцу (для поиска подстроки в строке с использованием методы хеширования)
 */

#include <iostream>
#include <vector>
using namespace std;
#define POW 31;

//хэш функция, которая преобразующая строку в числовое значение 
vector<long long> getHashPow(const string& text, const string& substring)
{
	int tLength = (int)text.length();
	int sLength = (int)substring.length();
	vector<long long> hashPow(max(sLength, tLength));
	hashPow[0] = 1;
	for (int i = 1; i < hashPow.size(); i++)
	{
		hashPow[i] = hashPow[i - 1] * POW;
	}

	return hashPow;
}

vector<long long> getPrefixHash(const string& text, const string& substring) //считаем хеши для всех префиксов из text
{
	int tLength = (int)text.length();
	vector<long long> hashPow = getHashPow(text, substring);
	vector<long long> hash(tLength);
	for (int i = 0; i < tLength; i++)
	{
		hash[i] = (text[i] - 'a' + 1) * hashPow[i];
		if (i)
		{
			hash[i] += hash[i - 1];
		}
	}
	return hash;
}

long long getSubstringHash(const string& text, const string& substring) //считаем хеши подстроки
{
	long long hash = 0;
	int sLength = (int)substring.length();
	vector<long long> hashPow = getHashPow(text, substring);
	for (int i = 0; i < sLength; i++)
	{
//желательно отнимать 'a' от кода буквы
 //единицу прибавляем, чтобы у строки вида 'aaaaa' хэш был ненулевой
		hash += (substring[i] - 'a' + 1) * hashPow[i]; 
	}
	return hash;
}

void getKPSearch(const string& text, const string& substring)
{
	int tLength = (int)text.length();
	int sLength = (int)substring.length();
	vector<long long> hashPow = getHashPow(text, substring);
	vector<long long> prefixHash = getPrefixHash(text, substring);
	long long substringHash = getSubstringHash(text, substring);
	for (int i = 0; i + sLength - 1 < tLength; i++)
	{
		long long result = prefixHash[i + sLength - 1];
		if (i)
		{
			result -= prefixHash[i - 1];
		}
		if (result == substringHash * hashPow[i]) // приводим хэши к одной степени и сравниваем
		{
			cout << i << " ";
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	string s, t;
	cout << "Введите текст" << "\n";
	cin >> t;
	cout << "Введите подстроку" << "\n";
	cin >> s;
	getKPSearch(t, s);
}


 