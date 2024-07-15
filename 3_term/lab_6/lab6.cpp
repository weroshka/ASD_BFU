//Сортировка посредством выбора 

//Сложность в любом случае : O(n^2)

#include <iostream>

//Ищем наименьшее значение в массиве 
int findSmallestPosition(int list[], int startPosition, int listLength)
{
	int smallestPosition = startPosition;

	for (int i = startPosition; i < listLength; i++)
	{
		if (list[i] < list[smallestPosition])
			smallestPosition = i;
	}
	return smallestPosition;
}

//Ставим наим значение на позицию, откуда начали проход
void selectionSort(int list[], int listLength)
{
	for (int i = 0; i < listLength; i++)
	{
		int smallestPosition = findSmallestPosition(list, i, listLength);
		std::swap(list[i], list[smallestPosition]);
	}
	return;
}

int main()
{
	int list[5] = { 12, 5, 48, 0, 4 };

	std::cout << "Input array ..." << std::endl;
	for (int i = 0; i < 5; i++)
		std::cout << list[i] << '\t';
	std::cout << std::endl;

	selectionSort(list, 5);

	std::cout << "Sorted array ..." << std::endl;
	for (int i = 0; i < 5; i++)
		std::cout << list[i] << '\t';
	std::cout << std::endl;
}