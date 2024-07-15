/*
 * Реализовать алгоритм Прима нахождения покрывающего дерева (это подмножество графа G, в котором все вершины покрыты минимально возможным числом ребер)
 */

#include <iostream>
#include <vector>
#include <map>
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
	Graph getPrimTree()
	{
		//вызывается конструктор графа
		Graph tree(size);
		//создаем ассоциативный контейнер
		map<int, vector<Rib>> ribs = getRibs();
		//создаем динамический массив узлов
		vector<int> nodes;
		//динамич. массив посещенных вершин
		vector<bool> visited(size, false);

		//берётся произвольная вершина и находится ребро, инцидентное данной вершине и обладающее наименьшей стоимостью
		int node1 = ribs[0][0].node1;
		int node2 = ribs[0][0].node2;
		int weight = ribs[0][0].weight;
		int totalWeight = weight;

		//относим эти вершины к пройденным
		visited[node1] = true;
		visited[node2] = true;

		//создаем дерево из двух вершин
		tree.connectNodes(node1, node2, weight);
		nodes.push_back(node1);
		nodes.push_back(node2);

		//разделяем вершины графа на два множества (обработанные и необработанные)
		// Затем, рассматриваются рёбра графа, один конец которых — уже принадлежащая дереву вершина, а другой — нет; 
		//из этих рёбер выбирается ребро наименьшей стоимости. 
		//Выбираемое на каждом шаге ребро присоединяется к дереву. Рост дерева происходит до тех пор, пока не будут исчерпаны все вершины исходного графа.
		for (int i = 0; i < size; i++)
		{
			for (auto& rib : ribs[i])
			{
				node1 = rib.node1;
				node2 = rib.node2;
				weight = rib.weight;
				//				cout << node1 << "  /  " << visited[node1] << "   ->   " << node2 << "  /  " << visited[node2] << "\n";
				if (visited[node1] != visited[node2])
				{
					tree.createRib(rib);
					visited[node1] = true;
					visited[node2] = true;
					nodes.push_back(node1);
					nodes.push_back(node2);
					totalWeight += weight;
				}
			}
		}
		cout << "weight = " << totalWeight << "\n";
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
	setlocale(LC_ALL, "Russian");
	Graph wg(5);
	wg.connect(0, 1, 3);
	wg.connect(0, 4, 1);
	wg.connect(1, 2, 5);
	wg.connect(1, 4, 4);
	wg.connect(2, 3, 2);
	wg.connect(2, 4, 6);
	wg.connect(3, 4, 7);
	wg.print();

	cout << "\n" << "прим" << "\n";

	Graph tree = wg.getPrimTree();

	tree.print();
}

