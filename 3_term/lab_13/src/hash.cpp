//hash.ccp - файл, где реализуем функции

//об€зательно должны подключить в него hpp файл
#include "hash.hpp"
#include <iostream>
//подключение библиотеки ввода\вывода
#include <fstream>

//объ€вление собственного пространства имен
namespace vk
{
	//функци€ возвращени€ индекса элемента
	int index(int a)
	{
		//вычисл€ем индекс дл€ вставки в массив делением числа на размерность массива
		int b = a % N;
		return b;
	}

	//реализаци€ работы хэш таблицы
	void HashTable(int mas[N][N], int a)
	{
		//возвращаетс€ индекс элемента
		int b = index(a);

		//если в массиве значение не зан€то, пишем в него число а
		if (mas[b][0] == 0)
			mas[b][0] = a;
		//если зан€то, то делаем перебор до тех пор, пока не встретим свободную €чейку 
		else
		{
			for (int i = 1; i < N; i++)
			{
				if (mas[b][i] == 0)
				{
					//как только нашли, пишем туда число и выходим из цикла
					mas[b][i] = a;
					break;
				}
			}
		}
	}

	//функци€ инициализации пустого массива (нужна, чтобы данные в массив записывались корректно)
	void Inicialization(int mas[N][N])
	{
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++) 
				mas[i][j] = 0;
		}

	}

    //функци€ считывани€ данных из файла
	void Writing_res(int mas[n])
	{
		std::ifstream in("input.txt");
		//вводим элементы из файла до тех пор, пока элементы в файле есть
		for (int i = 0; i < n; i++) 
		{
			in >> mas[i];
		}
	}

	//функци€ вывода в консоль
	void out(int mas[N][N])
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mas[i][j] != 0)
					std::cout << mas[i][j] << " ";
			}
			//чтобы выводить в столбик
			std::cout << std::endl;
		}
	}

	//функци€ вывода в файл
	void output(int mas[N][N]) 
	{
		std::ofstream out("out.txt");
		for (int i = 0; i < N; i++)
		{
			out << "key " << i << "= ";
			for (int j = 0; j < N; j++)
			{
				if (mas[i][j] != 0)
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
			if (mas[k][i] != 0)
				std::cout << mas[k][i] << " ";
			else
				break;
		}
	}
}
