//см комментарии к ЛР-13
#include "hash.hpp"
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream in("input.txt");

	int hashtable[N][N];
	vk::Inicialization(hashtable);

	int mas[n];
	vk::Writing_res(mas);

	for (int i = 0; i < n; i++) 

		vk::HashTable(hashtable, mas[i]);

	vk::out(hashtable);
	vk::output(hashtable);
	
}
