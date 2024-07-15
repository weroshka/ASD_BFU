//������������ ����������� ����� hpp
#include "hash.hpp"
#include <iostream>
//����������� ���������� �����\������
#include <fstream>

//���������� ������������ ����
namespace vk
{
	//����������-�������� 
	int i = 0;

	//������� ����������� ������� (�� ����� ���������� �����-������ ��������)
	int index(int a)
	{
		//��������� ������ ��� ������� � ������ �������� ����� �� ����������� ������� � ����������� i
		int b = a % N + i;
		return b;
	}

	//���������� ���-�������
	void HashTable(int mas[N][N], int a)
	{
		//������ ������������ �����
		while (1) 
		{
			//�������� ������ ����� �, ������� �������� �� ���� � ������� HashTable ������ � ��������
			int b = index(a);
			//���� �� ������� ������� ����� �������� ����� (����� �� ������ == �������, ���������� � ������� ����� -1), ����� ���
			if (mas[b][0] == -1) 
			{
				mas[b][0] = a;
				i = 0;
				break;
			}
			//����� ����������� i, ����� �������� ������ ������
			else 
				i++;
		}
	}

	//������� ������������� ������� �������
	void Inicialization(int mas[N][N])
	{
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) 
			{
				//������ �������� ������� -1
				mas[i][j] = -1;
			}
		}

	}

    //������� ���������� ������ �� �����
	void Writing_res(int mas[n])
	{
		std::ifstream in("input.txt");
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
				if (mas[i][j] != -1) 
					std::cout << mas[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	//������� ������ � ����
	void output(int mas[N][N]) 
	{
		std::ofstream out("out_2.txt");
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (mas[i][j] != -1)
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
			if (mas[k][i] != -1) 
				std::cout << mas[k][i] << " ";

			else 
				break;
		}

	}
}
