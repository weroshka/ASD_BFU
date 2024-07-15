//обязательное подключение файла hpp
#include "hash.hpp"
#include <iostream>
//подключение библиотеки ввода\вывода
#include <fstream>

//объявление пространства имен
namespace vk
{
	//переменная-итератор 
	int i = 0;

	//функция определения индекса (на выход возвращает число-индекс элемента)
	int index(int a)
	{
		//вычисляем индекс для вставки в массив делением числа на размерность массива и добавлением i
		int b = a % N + i;
		return b;
	}

	//реализация хэш-таблицы
	void HashTable(int mas[N][N], int a)
	{
		//запуск бесконечного цикла
		while (1) 
		{
			//получаем индекс числа а, которое подается на вход в функцию HashTable вместе с массивом
			int b = index(a);
			//если по данному индексу можно записать число (место не занято == элемент, хранящийся в массиве равен -1), пишем его
			if (mas[b][0] == -1) 
			{
				mas[b][0] = a;
				i = 0;
				break;
			}
			//иначе увеличиваем i, чтобы получить другой индекс
			else 
				i++;
		}
	}

	//функция инициализации пустого массива
	void Inicialization(int mas[N][N])
	{
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) 
			{
				//делаем элементы равными -1
				mas[i][j] = -1;
			}
		}

	}

    //функция считывания данных из файла
	void Writing_res(int mas[n])
	{
		std::ifstream in("input.txt");
		for (int i = 0; i < n; i++) 
		{
			in >> mas[i];
		}
	}

	//функция вывода в консоль
	void out(int mas[N][N])
	{
		
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++) 
			{
				if (mas[i][j] != -1) 
					std::cout << mas[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	//функция вывода в файл
	void output(int mas[N][N]) 
	{
		std::ofstream out("out_2.txt");
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mas[i][j] != -1)
					out << mas[i][j] << " ";
			}
			out << std::endl;
		}
	}


	//возвращает ключ элемента
	int key(int y)
	{
		int a = index(y);
		return a;
	}

	//поиск числа по ключу
	void number(int mas[N][N], int k)
	{

		for (int i = 0; i < N; i++) 
		{
			if (mas[k][i] != -1) 
				std::cout << mas[k][i] << " ";

			else 
				break;
		}

	}
}
