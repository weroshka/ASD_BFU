/*
 * алгоритм нахождения эйлерова цикла в неориентированном графе, заданном матрицей смежности
 * эйлеров цикл - эйлеров путь, являющийся циклом, то есть замкнутый путь, проходящий через каждое ребро графа ровно по одному разу
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph 
{
private:
	vector<vector<int>> graph;
	int size;
public:
	Graph(int size) : size(size)
	{
		graph = vector<vector<int>>(size, vector<int>(size, 0));
	}

	void connectNodes(int node1, int node2) //заполняем по матрице смежности
	{
		graph[node1][node2] = 1;
	}

	void connect(int node1, int node2)
	{
		connectNodes(node1, node2);
		connectNodes(node2, node1);
	}

	//реализация цикла
	vector<int> getEulerCycle()
	{
		//задаем динамический двумерный массив для графа
		vector<vector<int>> gr = graph;
		//подключаем стек для хранения вершин
		stack <int> nodes({ 0 });
		//вектор для эйлерова цикла
		vector<int> cycle;
		bool hasFreeRib;
		//пок стек вершин не пуст 
		while (!nodes.empty())
		{
			//каждый раз выбираем верхний элемент, т.е. вершину
			int top = nodes.top();
			hasFreeRib = false;
			for (int i = 0; i < size; i++)
			{
				if (gr[top][i]) //если в матрице смежности 1 ребро
				{
					nodes.push(i);
					gr[top][i] = gr[i][top] = 0;
					hasFreeRib = true;
					break;
				}
			}
			/*Выбираем любое выходящее из вершины ребро, с одним условием:
			не выбираем мост, если есть другая возможность.
			Проходим вдоль выбранного ребра до другой вершины.Добавляем это ребро в цикл и удаляем его из графа.*/
			if (!hasFreeRib)
			{
				cycle.push_back(top);
				nodes.pop();
			}
		}
		return cycle;
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << i << ":";
			for (int j = 0; j < size; j++)
			{
				if (graph[i][j])
				{
					cout << " " << j << "(" << graph[i][j] << ")";
				}
			}
			cout << "\n";
		}
	}

	void printCycle()
	{
		vector<int> cycle = getEulerCycle();
		for (auto node : cycle)
		{
			cout << node << " ";
		}
		cout << "\n";
	}

};


int main()
{
	Graph wg(6);
	wg.connect(0, 1);
	wg.connect(0, 4);
	wg.connect(1, 2);
	wg.connect(1, 4);
	wg.connect(1, 5);
	wg.connect(2, 3);
	wg.connect(2, 4);
	wg.connect(2, 5);
	wg.connect(3, 4);
	wg.print();

	wg.printCycle();
}

