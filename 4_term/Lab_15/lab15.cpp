//Решить задачу о раскраске графа

//способ раскрасить вершины Graph таким образом, чтобы никакие две соседние вершины не имели одинаковый цвет

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

// Структура данных для хранения ребра Graph
struct Edge {
    int src, dest;
};

class Graph
{
public:
    // вектор векторов для представления списка смежности
    vector<vector<int>> adjList;

    // Конструктор
    Graph(vector<Edge> const& edges, int n)
    {
        // изменить размер вектора, чтобы он содержал `n` элементов типа `vector<int>`
        adjList.resize(n);

        // добавляем ребра в неориентированный graph
        for (Edge edge : edges)
        {
            int src = edge.src;
            int dest = edge.dest;

            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
    }
};

// Добавляем больше цветов для graphs с большим количеством вершин
string color[] =
{
    "", "BLUE", "GREEN", "RED", "YELLOW", "ORANGE", "PINK",
    "BLACK", "BROWN", "WHITE", "PURPLE", "VOILET"
};

// Функция для присвоения цвета вершинам Graph
void colorGraph(Graph const& graph, int n)
{
    // отслеживаем цвет, присвоенный каждой вершине
    unordered_map<int, int> result;

    // назначаем цвет вершине одну за другой
    for (int u = 0; u < n; u++)
    {
        // устанавливаем для хранения цвета смежных вершин `u`
        set<int> assigned;

        // проверяем цвета смежных вершин `u` и сохраняем их в наборе
        for (int i : graph.adjList[u])
        {
            if (result[i]) {
                assigned.insert(result[i]);
            }
        }

        // проверяем первый свободный цвет
        int color = 1;
        for (auto& c : assigned)
        {
            if (color != c) {
                break;
            }
            color++;
        }

        // назначаем вершине `u` первый доступный цвет
        result[u] = color;
    }

    for (int v = 0; v < n; v++)
    {
        cout << "The color assigned to vertex " << v << " is "
            << color[result[v]] << endl;
    }
}

// Жадная раскраска Graph
int main()
{
    // vector ребер Graph согласно схеме выше
    vector<Edge> edges = {
        {0, 1}, {0, 4}, {0, 5}, {4, 5}, {1, 4}, {1, 3}, {2, 3}, {2, 4}
    };

    // общее количество узлов в Graph (от 0 до 5)
    int n = 6;

    // строим graph из заданных ребер
    Graph graph(edges, n);

    // цветной Graph с использованием жадного алгоритма
    colorGraph(graph, n);

    return 0;
}
