/*
 * Найти в заданном графе количество и состав компонент связности (максимально связный подграф в графе) с помощью поиска в глубину
 */

#include <iostream>
#include <vector>
//для реализации инвертированного обхода
#include <stack>
using namespace std;

class Graph 
{
private:
	//двумерный динамический массив для хранения графа
	vector<vector<int>> graph;
	//массив "посещенных" вершин
	vector<bool> visited;
	int size;
public:
	//создание графа
	Graph(int size) : size(size)
	{
		graph = vector<vector<int>>(size, vector<int>(size, 0));
		visited = vector<bool>(size, false);
	}

	void connectNodes(int node1, int node2)
	{
		graph[node1][node2] = 1;
	}

	void connectGraph(int node1, int node2) //имеем неориетированный граф(все вершины компоненты связности достижимы друг из друга)
	{
		connectNodes(node1, node2);
		connectNodes(node2, node1);
	}

	//задаем двумерный динамический массив для подсчета компонент связности
	vector<vector<int>> countComponents()
	{
		//проводим реализацию с помощью стека
		stack<int> s;
		//задаем двумерный массив, где будут храниться номера компонент
		vector<vector<int>> components;
		for (int i = 0; i < size; i++)
		{
			//если вершина была посещена, пропускаем ее
			if (visited[i])
			{
				continue;
			}
			//если не была посещена, добавляем номер вершины в очередь
			s.push(i);
			//отмечаем ее как пройденную
			visited[i] = true;
			//записываем номер компоненты
			vector<int>component(1, i);
			//пока стек не пустой
			while (!s.empty())
			{
				//запоминаем вершину стека
				int top = s.top();
				//удаляем ее
				s.pop();
				//добавляем компоненты для каждой вершины в массив
				for (int j = 0; j < size; j++)
				{
					if (!visited[j] && graph[top][j])
					{
						visited[j] = true;
						s.push(j);
						component.push_back(j);
					}
				}
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
	Graph graph(9);
	graph.connectGraph(0, 1);
	graph.connectGraph(0, 2);
	graph.connectGraph(1, 3);
	graph.connectGraph(1, 4);
	graph.connectGraph(2, 5);
	graph.connectGraph(3, 6);
	graph.connectGraph(7, 8);

	//	Graph graph(6);
	//	graph.connectGraph(0, 2);
	//	graph.connectGraph(2, 3);
	//	graph.connectGraph(2, 5);
	//	graph.connectGraph(1, 4);

	graph.print();
}
