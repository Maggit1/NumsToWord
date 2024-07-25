#include <iostream>
#include <string>
#include <locale>
#include <windows.h>

std::string units[] = { "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
std::string unitsFem[] = { "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
std::string teens[] = { "десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать" };
std::string tens[] = { "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто" };
std::string hundreds[] = { "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот" };

std::string convertNumber(int n, bool isMillion, bool isThousand);  //Объявления функций хранятся в сегменте кода (.text) программы. 
std::string numToWords(int n);                                       //Они не занимают память, так как это только объявления, а не определения функций.

int main()
{
    std::setlocale(LC_ALL, "RU");
    //SetConsoleOutputCP(CP_UTF8);
    int number;
    std::cout << "Введите число до 999999999: ";
    std::cin >> number;

    // проверяем, что число в допустимом диапазоне
    if (number < 0 || number > 999999999)
    {
        std::cout << "Число вне диапазона!" << std::endl;
        return 1; // завершаем программу с ошибкой
    }

    std::cout << numToWords(number) << std::endl;
    return 0;
}


// Функция для преобразования числа от 1 до 999 в слова
std::string convertNumber(int n, bool isMillion, bool isThousand) 
{
    if (n == 0) return "";

    std::string result;

    if (n >= 100)
    {                      //преобразование сотней
        result += hundreds[n / 100 - 1]; // добавляем слово для сотен
        n %= 100;                        // Убираем сотни из числа
        if (n > 0) result += " ";        // добавляем пробел, если есть остаток
    }

    if (n >= 20)
    {  // преобразуем 20-99
        result += tens[n / 10 - 2];
        n %= 10;
        if (n > 0) result += " ";
    }
    else if (n >= 10) // преобразуем 10-19
    { 
        result += teens[n - 10];
        n = 0;
    }

    if (n > 0) // преобразуем единицы
    {    
        if (isThousand) 
        {
            result += unitsFem[n - 1]; // используем женский род для тысяч
        }
        else 
        {
            result += units[n - 1]; // используем мужской род для остальных
        }
    }

    if (isMillion) // добавляем правильный суффикс в зависимости от миллиона или тысячи
    {   
        if (n == 1) result += " миллион";                 // для 1 миллиона
        else if (n >= 2 && n <= 4) result += " миллиона"; // для 2-4 миллионов
        else result += " миллионов";                      // для остальных случаев
    }
    else if (isThousand) 
    {
        if (n == 1) result += " тысяча"; // для 1 тысячи
        else if (n >= 2 && n <= 4) result += " тысячи"; // для 2-4 тысяч
        else result += " тысяч"; // для остальных случаев
    }

    return result; // возвращаем итоговый результат
}

// функция для проверки и разбиения числа
std::string numToWords(int n) 
{
    if (n == 0) return "ноль";
    std::string result;

    if (n >= 1000000) // преобразуем миллионы, если они есть 
    {                                    
        result += convertNumber(n / 1000000, true, false) + " "; // добавляем миллионы и пробел
        n %= 1000000;
    }

    if (n >= 1000)  // преобразуем тысячи, если они есть
    {                                     
        result += convertNumber(n / 1000, false, true) + " "; // добавляем тысячи и пробел
        n %= 1000;
    }

    if (n > 0) result += convertNumber(n, false, false);      // преобразуем оставшуюся часть числа

    return result; // возвращаем итоговый результат
}

