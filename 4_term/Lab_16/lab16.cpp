//Решить дискретную задачу о рюкзаке

#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

struct Good
{
	string name;
	int weight;
	int price;
	Good(string name, int weight, int price) : name(std::move(name)), weight(weight), price(price) {}
};

class Knapsack
{
private:
	int size;
	vector<Good> knapsack;

public:
	explicit Knapsack(int weight) : size(weight)
	{
		knapsack = vector<Good>();
	}

	void addGood(const Good& good)
	{
		knapsack.emplace_back(good.name, good.weight, good.price);
	}

	vector<Good> getGoods()
	{
		vector<Good> goods;
		for (const auto& k : knapsack)
		{
			goods.emplace_back(k.name, k.weight, k.price);
		}
		return goods;
	}

	void getMaxValue()
	{
		//кол-во комбинаций = 2^n, где n - количество предметов
		int totalPrice = 0, totalWeight = 0;
		string totalNamesCombination;
		vector<Good> goods = getGoods();
		int goodsSize = (int)goods.size();
		auto combinations = pow(2, goodsSize); //количество итераций

		for (int i = 0; i < combinations; i++)
		{
			int iNumber = i;
			vector<int> binaryForce(goodsSize, 0);
			int currentWeight = 0, currentPrice = 0;
			string currentNamesCombination, testWeight;

			for (int j = 0; j < goodsSize; j++) //полный перебор
			{
				binaryForce[j] = iNumber & 1; //побитово записываем число i
				iNumber >>= 1; //побитово сдвигаем i
			}

			for (int k = 0; k < goodsSize; k++)
			{
				if (binaryForce[k])
				{
					currentWeight += goods[k].weight;
					currentPrice += goods[k].price;
					currentNamesCombination += goods[k].name + ", ";
					testWeight += to_string(goods[k].weight) + "+";
				}
			}
			if (currentWeight <= size && currentWeight > totalWeight && currentPrice > totalPrice)
			{
				totalWeight = currentWeight;
				totalPrice = currentPrice;
				totalNamesCombination = currentNamesCombination;
			}
		}
		cout << "Комбинация товаров: " << totalNamesCombination << "\n";
		cout << "Итоговый вес всех товаров: " << totalWeight << "\n";
		cout << "Итоговая стоимость всех товаров: " << totalPrice << "\n";
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");
	Knapsack knapsack(10);
	knapsack.addGood(Good("гитара", 1, 10));
	knapsack.addGood(Good("пила", 2, 20));
	knapsack.addGood(Good("цветы", 5, 5));
	knapsack.addGood(Good("скрипка", 4, 10));
	knapsack.addGood(Good("ожерелье", 10, 30));
	knapsack.getMaxValue();

}