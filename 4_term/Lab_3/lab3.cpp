/*
 * Найти в заданном графе количество и состав компонент связности с помощью поиска в ширину
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph 
{
private:
	int size;
	//двумерный динамический массив для хранения графа
	vector<vector<int>> graph;
	//массив "посещенных" вершин
	vector<bool> visited;

public:
	//конструктор создания графа
	Graph(int size) : size(size)
	{
		graph = vector<vector<int>>(size, vector<int>(size, 0));
		visited = vector<bool>(size, false);
	}

	void connectNodes(int node1, int node2)
	{
		graph[node1][node2] = 1;
	}

	void connectGraph(int node1, int node2) //имеем неориетированный граф (все вершины компоненты связности достижимы друг из друга)
	{
		connectNodes(node1, node2);
		connectNodes(node2, node1);
	}

	//задаем двумерный динамический массив для подсчета компонент связности
	vector<vector<int>> countComponents()
	{
		//проводим реализацию с помощью очереди
		queue <int> q;
		//задаем двумерный массив, где будут храниться номера компонент
		vector<vector<int>> components;

		for (int i = 0; i < size; i++)
		{
			//если вершина была посещена, пропускаем ее
			if (visited[i])
			{
				continue;
			}
			//если не была посещена, добавляем номер вершины в стек
			q.push(i);
			//отмечаем ее как пройденную
			visited[i] = true;
			//записываем номер компоненты в массив компонент
			vector<int>component(1, i);
			//			int cur = 0;
			//пока очередь не пуста
			while (!q.empty())
			{
				for (int j = 0; j < size; j++)
				{
					//запоминаем первый элемент очереди
					int top = q.front();
					//добавляем компоненты для каждой вершины в массив
					if (!visited[j] && graph[top][j])
					{
						visited[j] = true;
						q.push(j);
						component.push_back(j);
					}
				}
				//удаляем вершину
				q.pop();
			}
			components.push_back(component);
		}
		visited = vector<bool>(size, false);
		return components;
	}

	void print()
	{
		vector<vector<int>> components;
		components = countComponents();
		for (int i = 0; i < components.size(); i++)
		{
			cout << "component №" << i + 1 << ":";

			auto component = components[i];
			for (int node : component)
			{
				cout << node << " ";
			}
			cout << "\n";
		}
	}
};

int main()
{
	//	Graph graph(9);
	//	graph.connectGraph(0, 1);
	//	graph.connectGraph(0, 2);
	//	graph.connectGraph(1, 3);
	//	graph.connectGraph(1, 4);
	//	graph.connectGraph(2, 5);
	//	graph.connectGraph(3, 6);
	//	graph.connectGraph(7, 8);

	Graph graph(6);
	graph.connectGraph(0, 2);
	graph.connectGraph(2, 3);
	graph.connectGraph(2, 5);
	graph.connectGraph(1, 4);

	graph.print();

	return 0;
}

