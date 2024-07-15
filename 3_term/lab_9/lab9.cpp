//Пирамидальная (heap sort)

//В худшем случае требуется n·log2n шагов, сдвигающих элементы

#include <iostream>
using namespace std;

// функция heapify для нагромождения дерева
void heapify(int arr[], int n, int root)
{
    int largest = root; // корень - самый большой элемент
    int l = 2 * root + 1; // слева = 2*корень + 1
    int r = 2 * root + 2; // справа = 2*корень + 2

    // Если левый дочерний элемент больше корневого
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Если правый дочерний элемент больше, чем самый большой на данный момент
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Если самый большой не является корневым
    if (largest != root)
    {
        //поменять местами корневой и самый большой
        swap(arr[root], arr[largest]);

        // Рекурсивное нагромождение поддерева
        heapify(arr, n, largest);
    }
}

// реализация сортировки кучи
void heapSort(int arr[], int n)
{
    // создать кучу
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // извлечение элементов из кучи один за другим
    for (int i = n - 1; i >= 0; i--)
    {
        // Переместить текущий корень в конец
        swap(arr[0], arr[i]);

        // снова вызовите max heapify для уменьшенной кучи
        heapify(arr, i, 0);
    }
}

/* печать содержимого массива - служебная функция */
void displayArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// основная программа
int main()
{
    int heap_arr[] = { 4,17,3,12,9,6 };
    int n = sizeof(heap_arr) / sizeof(heap_arr[0]);
    cout << "Input array" << endl;
    displayArray(heap_arr, n);

    heapSort(heap_arr, n);

    cout << "Sorted array" << endl;
    displayArray(heap_arr, n);
}