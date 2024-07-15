//hash.ccp - ����, ��� ��������� �������

//����������� ������ ���������� � ���� hpp ����
#include "hash.hpp"
#include <iostream>
//����������� ���������� �����\������
#include <fstream>

//���������� ������������ ������������ ����
namespace vk
{
	//������� ����������� ������� ��������
	int index(int a)
	{
		//��������� ������ ��� ������� � ������ �������� ����� �� ����������� �������
		int b = a % N;
		return b;
	}

	//���������� ������ ��� �������
	void HashTable(int mas[N][N], int a)
	{
		//������������ ������ ��������
		int b = index(a);

		//���� � ������� �������� �� ������, ����� � ���� ����� �
		if (mas[b][0] == 0)
			mas[b][0] = a;
		//���� ������, �� ������ ������� �� ��� ���, ���� �� �������� ��������� ������ 
		else
		{
			for (int i = 1; i < N; i++)
			{
				if (mas[b][i] == 0)
				{
					//��� ������ �����, ����� ���� ����� � ������� �� �����
					mas[b][i] = a;
					break;
				}
			}
		}
	}

	//������� ������������� ������� ������� (�����, ����� ������ � ������ ������������ ���������)
	void Inicialization(int mas[N][N])
	{
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++) 
				mas[i][j] = 0;
		}

	}

    //������� ���������� ������ �� �����
	void Writing_res(int mas[n])
	{
		std::ifstream in("input.txt");
		//������ �������� �� ����� �� ��� ���, ���� �������� � ����� ����
		for (int i = 0; i < n; i++) 
		{
			in >> mas[i];
		}
	}

	//������� ������ � �������
	void out(int mas[N][N])
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mas[i][j] != 0)
					std::cout << mas[i][j] << " ";
			}
			//����� �������� � �������
			std::cout << std::endl;
		}
	}

	//������� ������ � ����
	void output(int mas[N][N]) 
	{
		std::ofstream out("out.txt");
		for (int i = 0; i < N; i++)
		{
			out << "key " << i << "= ";
			for (int j = 0; j < N; j++)
			{
				if (mas[i][j] != 0)
					out << mas[i][j] << " ";
			}
			out << std::endl;
		}
	}


	//���������� ���� ��������
	int key(int y)
	{
		int a = index(y);
		return a;
	}

	//����� ����� �� �����
	void number(int mas[N][N], int k)
	{

		for (int i = 0; i < N; i++)
		{
			if (mas[k][i] != 0)
				std::cout << mas[k][i] << " ";
			else
				break;
		}
	}
}
