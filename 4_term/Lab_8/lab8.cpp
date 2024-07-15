/*
 * Реализовать алгоритм Дейкстры поиска кратчайших путей из одной вершины
 */



#include <iostream>
#include <algorithm>
#include <vector>
//для подключения множества
#include <map>
//контейнер, который автоматически сортирует добавляемые элементы в порядке возрастания
#include <set>
using namespace std;


//создаем структуру, с помощью которой конструируем дерево
struct Rib
{
	int node1;
	int node2;
	int weight;

	Rib(int node1, int node2, int weight) :
		node1(node1), node2(node2), weight(weight) {}
};

//создаем структуру, с помощью которой создаем вершины и определяем их вес
struct Node 
{
	int node, weight;
	Node(int node, int weight) : node(node), weight(weight) {}
	bool operator < (Node n) const
	{
		return weight < n.weight;
	}
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

	void connect(int node1, int node2, int weight)
	{
		connectNodes(node1, node2, weight);
		connectNodes(node2, node1, weight);
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

	map<int, vector<Rib>> getRibs()
	{
		map<int, vector<Rib>> ribs;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				int weight = graph[i][j];
				if (weight)
				{
					ribs[i].push_back(Rib(i, j, weight));
				}
			}
			sort(ribs[i].begin(), ribs[i].end(), compareRibs);
		}
		return ribs;
	}


	//реализация алгоритма
	void searchDjykstra(int currentNode)
	{
		//подключаем ассоциативный контейнер, в который поместим ребра графа с информацией об их весе 
		map<int, vector<Rib>> ribs = getRibs();
		//подключаем динамич. массив, чтобы считать расстояние от вершины до графа
		vector<int> distance(size, INT_MAX);
		//подключаем контейнер, типом данных которого будет структура Node
		set<Node> queue;

		//на данный момент расстояние равно 0
		distance[currentNode] = 0;

		//каждому соседнему узлу присваиваем накопленную стоимость 
		for (auto rib : ribs[currentNode])
		{
			distance[rib.node2] = rib.weight;
			queue.insert(Node(rib.node2, distance[rib.node2]));
		}
		
		//найти узел с наим накопленной стоимостью и сделать его постоянным
		for (auto node : queue)
		{
			for (auto rib : ribs[node.node])
			{
				if (distance[node.node] + rib.weight < distance[rib.node2])
				{
					distance[rib.node2] = distance[node.node] + rib.weight;
					queue.insert(Node(rib.node2, distance[rib.node2]));
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			cout << "# " << i << "  (" << distance[i] << ")" << "\n";
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
	setlocale(LC_ALL, "russian");
	int node = 0;
	
	Graph wg(5);
	wg.connect(0, 1, 3);
	wg.connect(0, 4, 1);
	wg.connect(1, 2, 5);
	wg.connect(1, 4, 4);
	wg.connect(2, 3, 2);
	wg.connect(2, 4, 6);
	wg.connect(3, 4, 7);
	wg.print();

	cout << "\n" << "дейкстра" << "\n";

	wg.searchDjykstra(node);
}

