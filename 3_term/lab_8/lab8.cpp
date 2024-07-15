// корневая (поразрядная) сортировка

//сложность O(wn), где n - кол-во элементов, каждый из к-х состоит из w цифр или символов 
#include <iostream>

using namespace std;

//кол-во цифр 
const int n = 10;
//кол-во разрядов
const int col_razr = 4;

int find_razryad(int number, int razryad)
{
    while (razryad > 1)
    {
        number /= 10;
        razryad--;
    }
    return number % 10;
}

void sort_razr(int dop_mas[n][n], int mas[n], int razr)
{
    int mas_col[n], i, j, temp = 0;
    for (i = 0; i < n; i++)
     mas_col[i] = 0;
    
    for (i = 0; i < n; i++)
    {
        int a = find_razryad(mas[i], razr);
        dop_mas[mas_col[a]][a] = mas[i];
        mas_col[a]++;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < mas_col[i]; j++)
        {
            mas[temp] = dop_mas[j][i];
            temp++;
        }
    }
}

int main()
{
    int razr, i;
    int mas[n] = { 45, 2, 78 };
    int dop_mas[n][n];
    for (razr = 1; razr < col_razr + 1; razr++)
        sort_razr(dop_mas, mas, razr);
    for (i = 0; i < n; i++)
        cout << mas[i] << endl;
    return 0;
}