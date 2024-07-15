#pragma once
//определение констант дл€ задани€ размерности массива
#define N 20
#define n 15

//определение собственного пространства имен
namespace vk
{
	//объ€вление функций, реализуемых в файле hash.cpp
	int index(int a);
	void HashTable(int mas[N][N], int a);
	void Inicialization(int mas[N][N]);
	void Writing_res(int mas[n]);
	void out(int mas[N][N]);
	void output(int mas[N][N]);
	int key(int y);
	void number(int mas[N][N], int k);
}