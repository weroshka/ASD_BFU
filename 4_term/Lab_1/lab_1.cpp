﻿#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

struct Point
{
    int x, y;
};

//Создаём нулевую точку для начала отсчета
Point p0;

//используем стек для нахождения ближайшей к нашей 
Point nextToTop(stack<Point>& S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}
//пишу функцию замены местами
void swap(Point& p1, Point& p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

//функция вычисления квадрата расстояния между точками  
int distSquare(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y);
}

//местоположение трёх точек 
//0 -->p,q и r коллинеарны
//1 --> по часовой
//2 --> против часовой
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; //точки на одной линии паралленльны
    return (val > 0) ? 1 : 2;//угол по часовой или против часовой 
    //Если Val >0, то вернуть 1, иначе 2
}

//сортируем точки в соответсвии с первой точкой
int compare(const void* vp1, const void* vp2)
{
    Point* p1 = (Point*)vp1;
    Point* p2 = (Point*)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSquare(p0, *p2) >= distSquare(p0, *p1)) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

//Рисуем выпуклую оболчку с n точками
void ConvexHull(Point points[], int n)
{
    //ищем нижнюю точку
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;

        //самую нижнюю или самую левую если нижних несколько
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
        // или || и &&
    }
    //делаем самую нижнюю точку первой
    swap(points[0], points[min]);

    /*сортируем n - 1 точку относительно первой
    p1 идёт до p2 в отсортированном виде если p2  имеет больший полярный угол
    (против часовой) чем p1*/
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    /*
    если две точки имеют один и тот же угол от p2 то выбираем ту что дальше
    */
    int m = 1;//определяем размер массива
    for (int i = 1; i < n; i++)
    {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++;//обновляем размер массива
    }
    //если размер массива меньше трёх точек то оболочки не сущесвтует
    if (m < 3) return;

    // Создаём пустой стек и пушим первые три точки туда
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    //Обрабатываем остальные n-3 точек
    for (int i = 3; i < m; i++)
    {
        /*
        Продолжаем убирать верхнюю часть пока угол из
        из точек сверху ,около и points[i] не сделают поворот направо*/
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }
    // теперь у стека есть выходные точки выведем стэк
    while (!S.empty())
    {
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y << ")" << endl;
        S.pop();
    }
}

int main()
{
    Point points[] = { {0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3} };
    int n = sizeof(points) / sizeof(points[0]);
    ConvexHull(points, n);
    return 0;
}
}