/*
 * Найти в заданном графе кратчайшие пути из заданной вершины до всех остальных вершин с помощью поиска в ширину
 */

#include <iostream>
//подключаем динамический массив
#include <vector>
//подключаем очередь
#include <queue>
using namespace std;

const int ribNumber = 4; //кол-во ребер графа
int startPosition = 0; //номер стартового узла графа
int matrix[ribNumber][ribNumber] =
{
		{0, 1, 0, 1},
		{0, 0, 1, 1},
		{0, 0, 1, 1},
		{1, 0, 1, 0},
};

//задействуем двумерный динамический массив и будем записывать в него граф
vector< vector<int> > read(int array[ribNumber][ribNumber])
{
	vector< vector<int> > graph;
	for (int i = 0; i < ribNumber; i++)
	{
		//будем передавать аргументы ф-ии emplace, чтобы передать конструктору, чтобы создать объект 
		graph.emplace_back();
		for (int j = 0; j < ribNumber; j++)
		{
			if (array[i][j])
			{
				//заполняем граф
				graph[i].push_back(j);
			}
		}
	}
	//выводим граф
	return graph;
}

//реализация поиска в ширину
vector <int> BFS()
{
	//задаем двумерный динамический массив, который заполняем графом
	vector< vector<int> > graph = read(matrix);
	//вызываем очередь
	queue<int> queue;
	//добавляем номер стартового узла графа,с которого начинается поиск, в изначально пустую очередь
	queue.push(startPosition);

	vector <bool> used(ribNumber);
	vector <int> length(ribNumber);
	used[startPosition] = true;

	while (!queue.empty())
	{
		int first = queue.front(); //запоминаем первый элемент
		queue.pop(); //удаляем его
		//запускаем цикл вширь графа
		for (int i = 0; i < graph[first].size(); ++i)
		{
			int rib = graph[first][i];
			//в конец очереди добавляются все преемники узла, которые ещё не развёрнуты и не находятся в очереди
			if (!used[rib])
			{
				used[rib] = true;
				queue.push(rib);
				length[rib] = length[first] + 1;
			}
		}
	}
	return length; //минимальное кол-во ребер
}

int main()
{
	setlocale(LC_ALL, "RUS");
	vector <int> length = BFS();
	for (int i = 0; i < ribNumber; i++)
	{
		if (i)
		{
			cout << "Расстояние до узла " << i << " = " << length[i] << "\n";
		}
	}
	return 0;
}
