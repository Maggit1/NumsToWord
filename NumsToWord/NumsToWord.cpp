#include <iostream>
#include <string>
#include <locale>
#include <windows.h>

std::string units[] = { "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
std::string unitsFem[] = { "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
std::string teens[] = { "десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать" };
std::string tens[] = { "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто" };
std::string hundreds[] = { "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот" };

std::string convertNumber(int n, bool isMillion, bool isThousand);
std::string numToWords(int n);
std::string getRubleWord(int n); 

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

    std::cout << numToWords(number) << " " << getRubleWord(number) << std::endl; // добавляем слово "рубль"

    return 0;
}

std::string convertNumber(int n, bool isMillion, bool isThousand)
{
    if (n == 0) return "";

    std::string result;

    if (n >= 100)
    {
        result += hundreds[n / 100 - 1];
        n %= 100;
        if (n > 0) result += " ";
    }

    if (n >= 20)
    {
        result += tens[n / 10 - 2];
        n %= 10;
        if (n > 0) result += " ";
    }
    else if (n >= 10)
    {
        result += teens[n - 10];
        n = 0;
    }

    if (n > 0)
    {
        if (isThousand)
        {
            result += unitsFem[n - 1];
        }
        else
        {
            result += units[n - 1];
        }
    }

    if (isMillion)
    {
        if (n == 1) result += " миллион";
        else if (n >= 2 && n <= 4) result += " миллиона";
        else result += " миллионов";
    }
    else if (isThousand)
    {
        if (n == 1) result += " тысяча";
        else if (n >= 2 && n <= 4) result += " тысячи";
        else result += " тысяч";
    }

    return result;
}

std::string numToWords(int n)
{
    if (n == 0) return "ноль";
    std::string result;

    if (n >= 1000000)
    {
        result += convertNumber(n / 1000000, true, false) + " ";
        n %= 1000000;
    }

    if (n >= 1000)
    {
        result += convertNumber(n / 1000, false, true) + " ";
        n %= 1000;
    }

    if (n > 0) result += convertNumber(n, false, false);

    return result;
}

std::string getRubleWord(int n)
{
    n %= 100;

    if (n >= 11 && n <= 19)
    {
        return "рублей";
    }

    int lastDigit = n % 10;

    switch (lastDigit)
    {
    case 1:
        return "рубль";
    case 2:
    case 3:
    case 4:
        return "рубля";
    default:
        return "рублей";
    }
}
