/*
 * Реализовать алгоритм Крускала нахождения покрывающего дерева.
 */

#include <iostream>
#include <vector>
#include <algorithm>
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

	//ф-я сравнения ребер
	static bool compareRibs(Rib a, Rib b)
	{
		return a.weight < b.weight;
	}

	//ф-я создания ребра
	void createRib(Rib rib)
	{
		connectNodes(rib.node1, rib.node2, rib.weight);
	}

	//ф-я создания дерева
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

	//ф-я получения ифнормации о ребре
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
		sort(rib.begin(), rib.end(), compareRibs);
		return rib;
	}

	//алгоритм 
	Graph getKruskalTree()
	{
		Graph tree(size);
		vector<Rib> ribs = getRibs();
		vector<int> components; //вектор с вершинами, которые мы посетим
		int totalWeight = 0;

		components.reserve(size);
		for (int i = 0; i < size; i++)
		{
			components.push_back(i);
		}

		for (auto& rib : ribs) // Проверяем вершины каждого ребра. Если вершины не принадлежат одному и тому же множеству,
			//то такое ребро добавляем в наше дерево, а вершины помещаем в одно множество
		{
			int node1 = rib.node1;
			int node2 = rib.node2;
			int weight = rib.weight;

			if (components[node1] != components[node2])
			{
				tree.createRib(rib);

				int old_variety = components[node2];
				int new_variety = components[node1];

				for (int k = 0; k < size; k++)
				{
					if (components[k] == old_variety)
					{
						components[k] = new_variety;
					}
				}
				totalWeight += weight;
			}

		}
		cout << "total weight: " << totalWeight << "\n";
		return tree;
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
	Graph wg(5);
	wg.connect(0, 1, 3);
	wg.connect(0, 4, 1);
	wg.connect(1, 2, 5);
	wg.connect(1, 4, 4);
	wg.connect(2, 3, 2);
	wg.connect(2, 4, 6);
	wg.connect(3, 4, 7);
	wg.print();

	cout << "\n" << "крускал" << "\n";

	Graph tree = wg.getKruskalTree();

	tree.print();
}
