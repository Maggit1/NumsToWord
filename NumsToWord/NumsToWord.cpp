#include <iostream>
#include <string>

using namespace std;

string ones[] = { "", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
string teens[] = { "десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать" };
string tens[] = { "", "десять", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто" };
string hundreds[] = { "", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот" };
string thousand_suffix[] = { "", "тысяча", "тысячи", "тысяч" };
string million_suffix[] = { "", "миллион", "миллиона", "миллионов" };

string convert_hundreds(int n) {
    string result = hundreds[n / 100];
    n %= 100;
    if (n >= 10 && n < 20) result += " " + teens[n - 10];
    else result += " " + tens[n / 10] + " " + ones[n % 10];
    return result;
}

string convert_number(int n, bool is_million) {
    if (n == 0) return "";
    string result = convert_hundreds(n);
    if (is_million) {
        if (n % 10 == 1 && n % 100 != 11) result += " миллион";
        else if (n % 10 >= 2 && n % 10 <= 4 && (n % 100 < 10 || n % 100 >= 20)) result += " миллиона";
        else result += " миллионов";
    }
    else {
        if (n % 10 == 1 && n % 100 != 11) result += " тысяча";
        else if (n % 10 >= 2 && n % 10 <= 4 && (n % 100 < 10 || n % 100 >= 20)) result += " тысячи";
        else result += " тысяч";
    }
    return result;
}

string num_to_words(int n) {
    if (n == 0) return "ноль";
    string result = "";
    if (n / 1000000 > 0) {
        result += convert_number(n / 1000000, true) + " ";
        n %= 1000000;
    }
    if (n / 1000 > 0) {
        result += convert_number(n / 1000, false) + " ";
        n %= 1000;
    }
    if (n > 0) result += convert_hundreds(n);
    return result;
}

int main() {
    setlocale(LC_ALL, "RU");
    int number;
    cout << "Введите число до 999999999: ";
    cin >> number;
    if (number < 0 || number > 999999999) {
        cout << "Число вне диапазона!" << endl;
        return 1;
    }
    cout << num_to_words(number) << endl;
    return 0;
}