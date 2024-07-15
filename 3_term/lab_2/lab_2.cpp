#include <iostream>

//подключение библиотеки для использования стека
#include <stack>

//подключение библиотеки для использования переменных типа std::string
#include <string>

using namespace std;

//функция проверки скобки (отсылка к 1 лр)
bool function(std::string s_string)
{
    // <тип данных> имя
    std::stack <char> C;

    for (int i = 0; i < s_string.length(); i++)
    {
        if ( (s_string[i] == '(') || (s_string[i] == '[') || (s_string[i] == '{')) 
            C.push(s_string[i]);

        if (C.empty() && (s_string[i] == ')' || s_string[i] == ']' || s_string[i] == '}')) 
            return false;

        //top - обращение к верхнему элементу списка
        if (s_string[i] == ')' && C.top() != '(') 
            return false;
        
        if (s_string[i] == ']' && C.top() != '[') 
            return false;
        
        if (s_string[i] == '}' && C.top() != '{') 
            return false;

        //удаление верхнего элемента стека
        if (s_string[i] == ')' && C.top() == '(') 
            C.pop();
        
        if (s_string[i] == ']' && C.top() == '[') 
            C.pop();

        if (s_string[i] == '}' && C.top() == '{') 
            C.pop();
    }

    if (C.empty()) 
        return true;

    return false;
}

//функция определения длины числа. Возвращает число целиком
string length(string str, int& j) 
{
    string len;
    for (int i = j; str[i] >= '0' && str[i] <= '9'; i++) 
    {
        len += str[i];
        j++;
    }
    j--;
    return len;
}

//функция подсчета выражения
int count(string str)
{
    // <тип данных> имя   
    std::stack <string> numbers; //числа
    
    std::stack <char> elements; //математические операции
    
    //переменные, которые будем использовать, 
    int a = 0;
    int b = 0;
    str += '=';
    
    for (int i = 0; str[i] != '='; i++)
    {
        //если перед нами начало числа, то вызываем функцию length, которая вернет число и сдвинет i в цикле for. Заносим число в стек  
        if (str[i] != '+' && str[i] != '-' && str[i] != '/' && str[i] != '*' && str[i] != '(' && str[i] != ')')
            numbers.push(length(str, i)); 

        //если перед нами математическая опреация, то
        if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*')
        {
            //если стек, куда мы добавляем мат.символы не пустой, то
            if (!elements.empty())
            {
                //считаем в порядке приоритета (* и / приоритетнее + и -)
                if ((str[i] == '+' || str[i] == '-') && (elements.top() == '/' || elements.top() == '*') && numbers.size() >= 2) 
                {
                    //преобразовываем числовую строку в целые числа
                    b = stoi(numbers.top());
                    
                    //удаление верхнего элемента стека
                    numbers.pop();
                    
                    a = stoi(numbers.top());
                    numbers.pop();
                    
                    // проверка деления на 0
                    if (b == '0' && elements.top() == '/') 
                    { 
                        cout << "error! division by zero! "; 
                        return 0; 
                    }

                    if (elements.top() == '/')
                        numbers.push(to_string(a / b));

                    if (elements.top() == '*')
                        numbers.push(to_string(a * b));
                    
                    //удаление верхнего элемента стека 
                    elements.pop();
                }
            }

            //если стек мат.символом не пустой
            if (!elements.empty())
            {
                //если данный элемент строки(мат символ) совпадает с тем элементом, что находится в начале стека мат. символов, то 
                if ((str[i] == '+' || str[i] == '-') && (elements.top() == '+' || elements.top() == '-') && numbers.size() >= 2)
                {
                    //преобразовываем числовую строку в целые числа
                    b = stoi(numbers.top());
                    //удаление верхнего элемента стека
                    numbers.pop();
                    
                    a = stoi(numbers.top());
                    numbers.pop();
                    
                    if (elements.top() == '+')
                        numbers.push(to_string(a + b));

                    if (elements.top() == '-')
                        numbers.push(to_string(a - b));
                }
            }
        }

        //если элемент исходной строки(которую нужно посчитать) равне скобке открывающей
        if (str[i] == '(') 
        {
            //объявляем подстроку, которую нужно посчитать
            string str2;
            
            int left_boarder = 1;
            int right_boarder = 0;
            
            //находит выражение внутри скобки
            for (int j = i + 1; left_boarder != right_boarder; j++) //i+1, т.к. смотрим на выражение без скобки
            {
                //записываем посимвольно
                str2 += str[j];
                if (str[j] == '(') 
                    left_boarder += 1;
                if (str[j] == ')') 
                    right_boarder += 1;
                i++;
            }
            //извлекаем элементы из стека
            str2.pop_back();

            //рекурсивно вызывает себя от выражения в скобке
            numbers.push(to_string(count(str2)));
        }

        if (!elements.empty())
        {
            if ((str[i] == '/' || str[i] == '*') && (elements.top() == '/' || elements.top() == '*'))
            {
                b = stoi(numbers.top());
                numbers.pop();
                a = stoi(numbers.top());
                numbers.pop();
                
                // проверка деления на 0, обязательна по условию
                if (b == '0' && elements.top() == '/') 
                { 
                    cout << "error! division by zero! ";
                    return 0;
                }

                if (elements.top() == '/' && b != '0')
                    numbers.push(to_string(a / b));
                
                if (elements.top() == '*')
                    numbers.push(to_string(a * b));
                
                //удаление верхнего элемента стека
                elements.pop();
                elements.push(str[i]);
            }

            if ((str[i] == '/' || str[i] == '*') && (elements.top() == '+' || elements.top() == '-')) 
                elements.push(str[i]);
            
            if ((str[i] == '+' || str[i] == '-') && (elements.top() != '/' && elements.top() != '*')) 
                elements.push(str[i]);
        }
        
        //добавляем самый первый элемент в стек символов
        if ((elements.empty() && (str[i] < '0' || str[i]>'9')) && str[i] != ')') 
            elements.push(str[i]); 
    }

    //пока стек элементов не пустой и в нем больше 2 чисел, в стеке с числами выполняются оставшиеся операции
    while (!elements.empty() && numbers.size() >= 2)
    {
        b = stoi(numbers.top());
        numbers.pop();
        a = stoi(numbers.top());
        numbers.pop();
        // проверка деления на 0, обязательна по условию
        if (b == 0 && elements.top() == '/') 
        { 
            cout << "error! division by zero! ";
            return 0;
        } 

        if (elements.top() == '/' && b != '0')
            numbers.push(to_string(a / b));

        if (elements.top() == '*')
            numbers.push(to_string(a * b));

        if (elements.top() == '+')
            numbers.push(to_string(a + b));

        if (elements.top() == '-')
            numbers.push(to_string(a - b));
        //удаление верхнего элемента стека
        elements.pop();
    }

    return stoi(numbers.top());
}

int main()
{
    std::string str;
    //ввод с консоли
    std::cin >> str; 
    printf("result is %d", count(str));
    
}