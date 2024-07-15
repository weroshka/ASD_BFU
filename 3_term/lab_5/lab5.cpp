// Сортировка вставками

//сложность в лучшем случае: O(n)
//Сложность в худшем случае : O(n^2)

#include <iostream>

int i, j, key = 0, temp = 0;

void InsertSort(int* mas, int n) 
{
	for (i = 0; i < n - 1; i++)
	{
		key = i + 1;
		temp = mas[key];
		for (j = i + 1; j > 0; j--)
		{
			//Перебираются элементы в неотсортированной части массива
			if (temp < mas[j - 1])
			{
				//Каждый элемент вставляется в отсортированную часть массива на то место, где он должен находиться.
				mas[j] = mas[j - 1];
				key = j - 1;
			}
		}
		mas[key] = temp;
	}
	std::cout << std:: endl << "Результирующий массив: ";
	for (i = 0; i < n; i++) //вывод массива
		std::cout << mas[i] << " ";
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int n;
	std::cout << "Количество элементов в массиве > "; std::cin >> n;
	int* mas = new int[n];
	for (i = 0; i < n; i++) //ввод массива
	{
		std::cout << i + 1 << " элемент > "; std::cin >> mas[i];
	}
	InsertSort(mas, n); //вызов функции
	delete[] mas;
	return 0;
}
