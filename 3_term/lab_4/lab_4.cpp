//Сортировка методом прочесывания

//Худшее время	O(n^2)
//Лучшее время	O(n logn)

#include <vector>
#include <iostream>

void comb(std::vector<int>& data) // передаём по ссылке, чтобы вызов comb(data) менял вектор data
{
	double factor = 1.247; // фактор уменьшения

	//находим длину массива и в зависимости от нее устанавливаем шаг сортировки
	int step = data.size()-1; 

	//Последняя итерация цикла, когда step==1 эквивалентна одному проходу сортировки пузырьком
	while (step >= 1)
	{
		for (int i = 0; i+step < data.size(); i++)
		{
			if (data[i] > data[i+step])
			{
				std::swap(data[i], data[i+step]);
			}
		}
		step /= factor;
	}
}

int main()
{
	std::vector<int> data = {9, 2, 6, 1};
	comb(data);
	for (int n : data)
		std::cout << n << "\n";
	return 0;
}