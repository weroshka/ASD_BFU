//Сортировка Шелла

//Сложность в лучшем и среднем случае: O(n* logn).
//Сложность в худшем случае: O(n^2).
#include <iostream>

void shellSort(int list[], int listLength)
{
	//исходный массив размером listLength разбивается на подмассивы с шагом listLength\2
	//Затем вновь разбиваются, но уже с шагом равным listLength\4
	//Когда шаг становится равен 1, массив просто сортируется вставками
	for (int step = listLength / 2; step > 0; step /= 2)
	{
		//сортировка вставками
		for (int i = step; i < listLength; i++)
		{
			int j = i;
			while (j >= step && list[j - step] > list[i])
			{
				std::swap(list[j], list[j - step]);
				j -= step;
				std::cout << "\n";
			}
		}
	}
}

int main()
{
	int list[8] = { 3,19,8,0,48,4,5,12 };
	std::cout << "Input array ...\n";
	for (int i = 0; i < 8; i++)
	{
		std::cout << list[i] << "\t";
	}

	shellSort(list, 8);

	std::cout << "\n\nSorted array ... \n";
	for (int i = 0; i < 8; i++)
	{
		std::cout << list[i] << "\t";
	}
}