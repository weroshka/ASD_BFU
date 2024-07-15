//Реализовать алгоритм Беллмана-Форда поиска кратчайших путей из одной вершины

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Rib
{
	int node1;
	int node2;
	int weight;

	Rib(int node1, int node2, int weight) :
		node1(node1), node2(node2), weight(weight) {}
};


class Graph {
private:
	vector<vector<int>> graph;
	int size;
public:
	Graph(int size) : size(size)
	{
		graph = vector<vector<int>>(size, vector<int>(size, 0));
	}

	void connectNodes(int node1, int node2, int weight) //заполняем по матрице весов
	{
		graph[node1][node2] = weight;
	}

	static bool compareRibs(Rib a, Rib b)
	{
		return a.weight < b.weight;
	}

	void createRib(Rib rib)
	{
		connectNodes(rib.node1, rib.node2, rib.weight);
	}

	void createTree(vector<Rib>& rib)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (graph[i][j])
				{
					rib.emplace_back(i, j, graph[i][j]);
				}
			}
		}
	}

	vector<Rib> getRibs()
	{
		vector<Rib> rib;
		createTree(rib);

		for (int i = 0; i < rib.size(); i++)
		{
			for (int j = i + 1; j < rib.size(); j++)
			{
				if (rib[i].node1 == rib[j].node2 && rib[i].node2 == rib[j].node1)
				{
					rib.erase(rib.begin() + j--);
				}
			}
		}
		std::sort(rib.begin(), rib.end(), compareRibs);
		return rib;
	}

	//реализация алгоритма
	void getBellmanFordSearch(int currentNode)
	{
		vector<Rib> ribs = getRibs();
		vector<int> distance(size, INT_MAX);
		distance[currentNode] = 0;

		// Вторым шагом вычисляются самые короткие расстояния.
		//Следующие шаги нужно выполнять | V | -1 раз, где | V | — число вершин в данном графе
		for (int i = 0; i < size - 1; i++) 
		{
			for (auto rib : ribs)
			{
				if (distance[rib.node1] != INT_MAX && (distance[rib.node1] + rib.weight) < distance[rib.node2])
				{
					distance[rib.node2] = distance[rib.node1] + rib.weight;
				}
			}
		}

		// На этом шаге сообщается, присутствует ли в графе цикл отрицательного веса
		for (auto rib : ribs) 
		{
			if (distance[rib.node1] != INT_MAX && (distance[rib.node1] + rib.weight) < distance[rib.node2])
			{
				cout << "граф содержит цикл отрицательного веса" << "\n";
			}
		}

		for (int i = 0; i < size; i++)
		{
			cout << currentNode << " -> " << i << '(' << distance[i] << ')' << "\n";
		}
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
};


int main()
{
	setlocale(LC_ALL, "Russian");

	int node = 0;
	Graph g(5);
	g.connectNodes(0, 1, -1);
	g.connectNodes(0, 2, 4);
	g.connectNodes(1, 2, 3);
	g.connectNodes(1, 3, 2);
	g.connectNodes(1, 4, 2);
	g.connectNodes(3, 2, 5);
	g.connectNodes(3, 1, 1);
	g.connectNodes(4, 3, -3);
	g.print();

	cout << "\n" << "Беллман-Форд" << "\n";
	g.getBellmanFordSearch(node);
}
