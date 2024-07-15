//подключение hpp файла для того, чтобы можно было пользоваться функциями из этого файла в main
#include "hash.hpp"
#include <iostream>
//подключение библиотеки ввода\вывода файла
#include <fstream>

int main()
{
	//подключаем считывание данных файла
	std::ifstream in("input.txt");

	//создаем двумерный массив
	int hashtable[N][N];
	//вызов функций
	
	vk::Inicialization(hashtable);

	int mas[n];
	vk::Writing_res(mas);

	for (int i = 0; i < n; i++) 

		vk::HashTable(hashtable, mas[i]);

	vk::output(hashtable);
	
}
