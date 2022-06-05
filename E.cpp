// Вам дано число, записанное римскими цифрами. Получите это же число в обычной записи (арабскими цифрами).
// Римская запись чисел может включать следующие символы:
// ’I’ — 1
// ’V’ — 5
// ’X’ — 10
// ’L’ — 50
// ’C’ — 100
// ’D’ — 500
// ’M’ — 1000
// Цифры ’I’, ’X’, ’C’ и ’M’ нельзя использовать более трех раз подряд.
// Цифры ’V’, ’L’ и ’D’ нельзя использовать более одного раза во всей записи числа.
// Обыкновенно цифры записывают по убыванию слева направо. Например, число 350 будет записано как ’CCCL’.
// Однако есть исключения:
// Чтобы получить ’4’ или ’9’, надо поставить ’I’ перед ’V’ или ’X’ соответственно
// Чтобы получить ’40’ или ’90’, надо поставить ’X’ перед ’L’ или ’C’.
// Чтобы получить ’400’ или ’900’, надо поставить ’C’ перед ’D’ или ’M’.
// Формат ввода
// В единственной строке дана запись числа римскими цифрами. Длина записи не превосходит 15.
// Формат вывода
// Выведите число, записанное арабскими цифрами. Если запись числа некорректная, то выведите -1.

#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>

using namespace std;

namespace
{
    unordered_map<string, int> romanToArabic = {
        {"I", 1},
        {"V", 5},
        {"X", 10},
        {"L", 50},
        {"C", 100},
        {"D", 500},
        {"M", 1000},
        {"IV", 4},
        {"IX", 9},
        {"XL", 40},
        {"XC", 90},
        {"CD", 400},
        {"CM", 900}
    };
}


int convertToArabic(const string& romanNumber) {
    unordered_map<char, bool> wasVLD = {
        {'V', false},
        {'L', false},
        {'D', false}
    };
    for (const char c: romanNumber)
    {
        for (auto& elem: wasVLD)
        {
            if (c == elem.first)
            {
                if (elem.second)
                {
                    return -1;
                }
                else
                {
                    elem.second = true;
                }
            }
        }
    }
    int arabicNumber = 0;
    int numberOrder = 0;
    for (int i = 0; i < romanNumber.size();)
    {
        int counter = 1;
        while ((i + counter < romanNumber.size()) &&
               (romanNumber[i] == romanNumber[i + counter]))
        {
            ++counter;
            if (counter > 3)
            {
                return -1;
            }
        }
        int currentNumber = -1;
        string currentStr = romanNumber.substr(i, 1);
        if (counter > 1)
        {
            currentNumber = counter * romanToArabic[currentStr];
            i += counter;
        }
        else
        {
            if ((i == romanNumber.size() - 1) ||
                (romanToArabic[currentStr] > romanToArabic[romanNumber.substr(i + 1, 1)]))
            {
                currentNumber = romanToArabic[currentStr];
                ++i;
            }
            else
            {
                currentStr.push_back(romanNumber[i + 1]);
                auto it = romanToArabic.find(currentStr);
                if (it != romanToArabic.end())
                {
                    currentNumber = it->second;
                    i += 2;
                }
                else
                {
                    return -1;
                }
            }
        }
        if (arabicNumber == 0)
        {
            numberOrder = int(log10(currentNumber));
        }
        else if(int(log10(currentNumber)) >= numberOrder)
        {
            return -1;
        }
        arabicNumber += currentNumber;
    }
    return arabicNumber;
}

int main() {
    string romanNumber;
    cin >> romanNumber;
    cout << convertToArabic(romanNumber);
}
