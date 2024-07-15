/*
 * Найти в заданном орграфе количество и состав сильно связных компонент (макс сильно связный подграф) с помощью поиска в глубину.
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
private:
	vector<vector<int>> graph;
	vector<bool> visited;
	int size;
public:
	Graph(int size) : size(size)
	{
		graph = vector<vector<int>>(size, vector<int>(size, 0));
		visited = vector<bool>(size, false);
	}

	void connectNodes(int node1, int node2) // имеем ориентированный граф
	{
		graph[node1][node2] = 1;
	}

	//определяем такой неориентированный граф, в котором для каждой такой пары содержится ребро
	vector<vector<int>> getReachabilityMatrix()
	{
		//задаем двумерный динамический массив для работы с графом
		vector<vector<int>> reachabilityMatrix;
		reachabilityMatrix = vector<vector<int>>(size, vector<int>(size, 0));
		for (int i = 0; i < size; i++)
		{
			stack<int> s;
			vector<int> depth;
			//отмечаем вершину под индексом как пройденную
			visited[i] = true;
			//добавляем ее номер в стек
			s.push(i);
			//добавляем индекс в массив, где храним инфу о глубине графа
			depth.push_back(i);
			//пока стек не пуст
			while (!s.empty())
			{
				//запоминаем вершину стека
				int top = s.top();
				//удаляем ее
				s.pop();
				//добавляем компоненты для каждой вершины в массив
				for (int j = 0; j < size; j++)
				{
					if (graph[top][j] && !visited[j])
					{
						visited[j] = true;
						s.push(j);
						depth.push_back(j);
					}
				}
			}

			for (int k : depth)
			{
				reachabilityMatrix[i][k] = 1;
			}
			visited = vector<bool>(size, false);
		}
		return reachabilityMatrix;
	}

	//ф-я транспонирования матрицы (чтобы проверить проверяем, достижима ли t из s и s из t, для всех пар s и t
	vector<vector<int>> getTransposedMatrix()
	{
		vector<vector<int>> reachabilityMatrix = getReachabilityMatrix();
		vector<vector<int>> transposedMatrix;
		transposedMatrix = vector<vector<int>>(size, vector<int>(size, 0));

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				transposedMatrix[i][j] = reachabilityMatrix[i][j] * reachabilityMatrix[j][i];
			}
		}
		return transposedMatrix;
	}


	//Поиск компонент связности неориентированного графа даёт компоненты сильной связности орграфа
	vector<vector<int>> countStrongComponents()
	{
		vector<vector<int>> components;
		vector<vector<int>> transposedMultipliedMatrix = getTransposedMatrix();

		for (int i = 0; i < size; i++)
		{
			if (visited[i])
			{
				continue;
			}
			visited[i] = true;
			vector<int> component;
			component = vector<int>(1, i);
			for (int j = i + 1; j < size; j++)
			{
				if (transposedMultipliedMatrix[i] == transposedMultipliedMatrix[j])
				{
					visited[j] = true;
					component.push_back(j);
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
		components = countStrongComponents();
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
	Graph graph(10);
	graph.connectNodes(0, 4);
	graph.connectNodes(0, 7);
	graph.connectNodes(4, 2);
	graph.connectNodes(2, 8);
	graph.connectNodes(2, 1);
	graph.connectNodes(2, 7);
	graph.connectNodes(8, 2);
	graph.connectNodes(7, 1);
	graph.connectNodes(7, 9);
	graph.connectNodes(1, 8);
	graph.connectNodes(1, 4);
	graph.connectNodes(3, 6);
	graph.connectNodes(6, 1);
	graph.connectNodes(6, 5);
	graph.connectNodes(5, 1);
	graph.connectNodes(5, 8);
	graph.connectNodes(5, 3);

	graph.print();
}

