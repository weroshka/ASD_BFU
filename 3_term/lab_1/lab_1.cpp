#include <iostream>

//подключение библиотеки для использования стека
#include <stack>

//подключение библиотеки для использования переменных типа std::string
#include <string>

//Функция проверки строки
int function(std::string s_string)
{
	// <тип данных> имя   
	std::stack <char> String;
	std::stack <int> C;

	//вводим строку
	std::cout << "Введите строку " << std::endl;
	std::cin >> s_string;
	int iterator = 0;

	if (s_string.length() % 2 != 0)
	{
		std::cout << "Неверно введена строка " << std::endl;
		return -1;
	}

	for (int i = 0; i < s_string.length(); i++)
	{

		if (String.empty() && (s_string[i] == ')' || s_string[i] == ']' || s_string[i] == '}'))
		{
			std::cout << "Неверно введена строка " << std::endl;
			return -1;
		}

		if (s_string[i] == ')' && String.top() != '(')
		{
			std::cout << "Неверно введена строка " << std::endl;
			return -1;
		}

		//top - обращение к верхнему элементу списка
		if (s_string[i] == ']' && String.top() != '[')
		{
			std::cout << "Неверно введена строка " << std::endl;
			return -1;
		}

		if (s_string[i] == '}' && String.top() != '{')
		{
			std::cout << "Неверно введена строка " << std::endl;
			return -1;
		}

		if ((s_string[i] == '(') || (s_string[i] == '[') || (s_string[i] == '{'))
		{
			iterator++;
			String.push(s_string[i]);
			C.push(iterator);
		}

		if (s_string[i] == ')' && String.top() == '(')
		{
			//удаление верхнего элемента стека
			String.pop();
			iterator++;
			printf("\n");
			printf("%d - %d", C.top(), iterator);
			C.pop();
		}

		if (s_string[i] == ']' && String.top() == '[')
		{
			String.pop();
			iterator++;
			printf("\n");
			printf("%d - %d", C.top(), iterator);
			C.pop();
		}

		if (s_string[i] == '}' && String.top() == '{')
		{
			String.pop();
			iterator++;
			printf("\n");
			printf("%d - %d", C.top(), iterator);
			C.pop();
		}
	}	
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::string string;
	function(string);
	
	return 0;
}