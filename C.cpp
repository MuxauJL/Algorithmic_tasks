// Вам дан массив натуральных чисел a[i].
// Найдите число таких пар элементов (a[i], a[j]), где ∣∣a[i] − a[j]∣∣ % 200 == 0 и i < j.

// Формат ввода
// В первой строке дан размер массива n (1 ≤ n ≤ 200000).
// Во второй строке через пробел записаны элементы массива a[i] (1 ≤ a[i] ≤ 10^9).

// Формат вывода
// Выведите единственное число — количество пар, подходящих под указанное выше условие.
  
#include <iostream>
#include <vector>

using namespace std;


long long getNumberOfGoodPairs(int n, const vector<int>& numbers) {
    if (n < 2)
    {
        return 0;
    }
    vector<int> modCounter(200, 0);
    for (int number: numbers)
    {
        modCounter[number % 200] += 1;
    }
    long long pairCounter = 0;
    for (int counter: modCounter)
    {
        pairCounter += (counter * (counter - 1)) >> 1;
    }
    return pairCounter;
}

int readInt() {
    int x;
    cin >> x;
    return x;
}

vector<int> readList(int n) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        cin >> res[i];
    }
    return res;
}

int main() {
    int n = readInt();
    vector<int> numbers = readList(n);
    cout << getNumberOfGoodPairs(n, numbers);
}
