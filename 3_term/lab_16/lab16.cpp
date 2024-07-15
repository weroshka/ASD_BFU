// Нерекурсивный прямой обход (реализуется с помощью стека)

#include <iostream>
#include <vector>
#include <string>

struct BinaryNode
{
	int value;

	//указатели на левый и правый узлы пока что равны nullptr
	BinaryNode* left = nullptr;
	BinaryNode* right = nullptr;

	//обработка исходной строки
	BinaryNode(std::string& s)
	{
		//получаем число
		value = getValue(s);
		//стираем с элемента с индексом 0 по элемент с индексом, который вычислим по функции digits
		s.erase(0, digits(value));
		//если первый элемент - это скобка, то снимаем ее
		if (s[0] == '(')
			s = unbracket(s);
		else
			return;

		//если первый элемент - это число (сделали проверку), то создаем узел
		if (isDigit(s[0]))
			left = new BinaryNode(s);
		//если имеется символ ",", то нужно строить правую ветвь по условию
		if (s[0] == ',' && isDigit(s[1]))
			right = new BinaryNode(s.erase(0, 1));
	}


private:
	//проверка на то, если перед нами число или же это скобка
	bool isDigit(char c)
	{
		//возвращаем символ, если он находится в пределах от 0 до 9
		return c >= '0' && c <= '9';
	}

	int digits(int n)
		//Если n = true, то функция выполняет округление значение и возвращает наибольшее целое значение, которое не больше, чем изначальное.
		//иначе возвращается 1
	{	//n - само число, которое мы считали, например, 0, 1 и тд
		if (n)
		{
			n = floor(log10(n) + 1);
			return n;
		}
		else
			return 1;
	}

	int getValue(std::string& s)
	{
		//получаем размерность строки (в нашем случае она равна 16)
		int n = s.size();
		int i = 1;
		while (i < n)
			//если за цифрой не следует другая цифра, выходим из цикла
			if (!isDigit(s[i++]))
				break;

		//возвращаем подстроку, начиная с символа с индексом 0 по i индекс символа строки, переводя числовую строку в целое число
		return std::stoi(s.substr(0, i));
	}

	//функция удаления скобки 
	std::string unbracket(std::string s)
	{
		for (int i = 1, d = 1; i < s.size(); i++, d += (s[i] == '(') - (s[i] == ')'))
			if (!d)
				return s.erase(0, 1).erase(i - 1, 1);
		return s;
	}
};

//реализация бинарного дерева
class BinaryTree
{
	//объявляем корень, пока что указывает ни на что
	BinaryNode* root = nullptr;

	//функция заполнения дерева
	void print(const std::string& p, const BinaryNode* n, bool l)
	{
		if (!n) return;
		std::cout << p << (l ? "|--" : "|--") << n->value << "\n";
		print(p + (l ? "|   " : "    "), n->left, 1);
		print(p + (l ? "|   " : "    "), n->right, 0);
	}

public:
	BinaryTree(std::string s) : root(new BinaryNode(s)) {}

	void print() { print("", root, 0); };

	//реализация нерекурсивного обхода
	void NonRecursive()
	{
		//объявляется вектор stack, в который помещен корень дерева
		std::vector<BinaryNode*> stack = { root };
		//пока стек не пуст
		while (!stack.empty())
		{
			//берем последний элемент стека в n, которое является структурой
			BinaryNode* n = stack.back();
			//затем удаляем этот последний элемент, сокращая длину стека на 1
			stack.pop_back();
			//выводим значение последнего элемента
			std::cout << n->value << " ";
			//устанавливаем его в нужную часть дерева
			if (n->right)
				stack.push_back(n->right);
			if (n->left)
				stack.push_back(n->left);
		}
		std::cout << "\n";
	}
};

int main()
{
	//вводим последовательность
	BinaryTree tree("0(1(3,4),2(5,6))");
	//печатаем дерево
	tree.print();
	//вызываем функцию нерекурсивного обхода
	tree.NonRecursive();
}