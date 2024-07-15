/*
 * алгоритм поиска по образцу с помощью конечного автомата
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

//функция, реализуемая через контейнер, которая на выходе будет выдавать алфавит  
map<char, int> getAlphabet(const string& s)
{
	map<char, int> alphabet;
	int i = 1;
	//считаем частоту употреблений каждого символа
	for (char c : s)
	{
		if (!alphabet[c])
		{
			alphabet[c] = i++;
		}
	}
	return alphabet;
}

//ф-я получения конечного автомата
vector<vector<int>> getFinalAutomaton(const string& s)
{
	//подключаем алфавит 
	auto alphabet = getAlphabet(s);
	//конечный автомат, принимающий заданную строку символов путём прохождения через последовательность состояний, 
	//определённых строкой
	auto DFA = vector<vector<int>>(s.size(), vector<int>(alphabet.size(), 0));
	//перовоначально автомат находится в начальном состоянии
	DFA[0][0] = 1;
	int length = 1;
	//по очереди читаем символы входной строки
	for (int i = 1; i < s.length(); i++)
	{
		//находясь в определенном состоянии автомат, читая символ, переходит в другое состояние
		DFA[i] = DFA[length];
		DFA[i][alphabet[s[i]] - 1] = i + 1;
		length = DFA[length][alphabet[s[i]] - 1];
	}
	return DFA;
}

void getSubstringSearch(const string& substring, const string& text)
{
	//высчитывается алфавит подстроки
	auto alphabet = getAlphabet(substring);
	//применяется детерминированный конечный автомат к подстроке
	auto DFA = getFinalAutomaton(substring);
	int tLength = (int)text.length();
	int sLength = (int)substring.length();
	for (int i = 0, state = 0; i < tLength; i++)
	{
		char c = text[i];
		if (alphabet[c])
		{
			state = DFA[state][alphabet[c] - 1];
		}
		if (!alphabet[c])
		{
			state = 0;
		}
		if (state == sLength)
		{
			cout << i - state + 1 << "\n";
		}
	}
}

void printAutomaton(const string& substring)
{
	auto DFA = getFinalAutomaton(substring);
	for (int i = 0; i < substring.length(); i++)
	{
		for (auto automaton : DFA[i])
		{
			cout << automaton << " ";
		}
		cout << "\n";
	}

}

int main()
{
	string text, substring;
	cout << "enter the text " << "\n";
	cin >> text;
	cout << "enter the substring " << "\n";
	cin >> substring;
	getSubstringSearch(substring, text);
	printAutomaton(substring);
}

