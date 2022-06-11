// Назовем строку хорошей, если в ней нет двух соседних букв, которые различаются только регистром.
// Например, строка «abba» хорошая, а строка «aBba» нет.
// Со строкой можно делать преобразование: если два соседних символа обозначают одну и ту же букву,
// но записаны в разных регистрах, то их можно удалить.
// При этом строка «схлопнется», то есть пробелов при удалении не образуется.
// Цепочкой таких преобразований можно превратить любую строку в хорошую.
// По заданной строке найдите хорошую строку, в которую ее можно превратить.
// Вы можете воспользоваться заготовками кода для данной задачи из репозитория курса.

// Формат ввода
// На вход подаётся строка, состоящая из больших и маленьких латинских букв.
// Длина строки не превосходит 10^5.
// Формат вывода
// Выведите хорошую строку, в которую можно превратить данную.

#include <iostream>

using namespace std;

string convertToGoodString(string stringToConvert) {
    if (stringToConvert.size() < 2)
    {
        return stringToConvert;
    }
    int curr = 0;
    for (int next = 2; next < stringToConvert.size();)
    {
        next = max(next, curr + 2);
        if ((tolower(stringToConvert[curr]) == tolower(stringToConvert[curr + 1]))
            && (stringToConvert[curr] != stringToConvert[curr + 1]))
        {
            if (next < stringToConvert.size())
            {
                stringToConvert[curr] = stringToConvert[next++];
            }
            if (curr > 0)
            {
                --curr;
            }
            else if (next < stringToConvert.size())
            {
                stringToConvert[curr + 1] = stringToConvert[next++];
            }
            else
            {
                stringToConvert[curr + 1] = -1;
            }
        }
        else
        {
            ++curr;
            stringToConvert[curr + 1] = stringToConvert[next++];
        }
    }
    if ((tolower(stringToConvert[curr]) == tolower(stringToConvert[curr + 1]))
        && (stringToConvert[curr] != stringToConvert[curr + 1]))
    {
        --curr;
    }
    else
    {
        ++curr;
    }
    stringToConvert.erase(curr + 1);
    return stringToConvert;
}

int main() {
    string probablyBadString;
    cin >> probablyBadString;
    cout << convertToGoodString(probablyBadString);
}
