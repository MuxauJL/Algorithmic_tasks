// На стол в ряд выложены карточки, на каждой карточке написано натуральное число.
// За один ход разрешается взять карточку либо с левого, либо с правого конца ряда.
// Всего можно сделать k ходов. Итоговый счет равен сумме чисел на выбранных карточках.
// Определите, какой максимальный счет можно получить по итогам игры.

// Формат ввода
// В первой строке записано число карточек 
// n (1 ≤ n ≤ 10^5).
// Во второй строке записано число ходов 
// k (1 ≤ k ≤ n).
// В третьей строке через пробел даны числа, записанные на карточках. 
// i-е по счету число записано на i-й слева карточке.
// Все числа натуральные и не превосходят 10^4.

// Формат вывода
// Выведите единственное число — максимальную сумму очков, которую можно набрать, сделав k ходов.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


long getCardCount(int n, int k, const vector<long long> &cards) {
    if (k == n)
    {
        return std::accumulate(cards.begin(), cards.end(), 0);
    }
    long long leftSum = std::accumulate(cards.begin(), cards.begin() + k, 0);
    long long rightSum = 0;
    long long maxSum = leftSum;
    for (int fromRight = 1; fromRight <= k; ++fromRight)
    {
        leftSum -= cards[k - fromRight];
        rightSum += cards[n - fromRight];
        maxSum = std::max(maxSum, leftSum + rightSum);
    }
    return maxSum;
}

int readInt() {
    int x;
    cin >> x;
    return x;
}

vector<long long> readList(int n) {
    vector<long long> res(n);
    for (int i = 0; i < n; i++) {
        cin >> res[i];
    }
    return res;
}

int main() {
    int n = readInt();
    int k = readInt();
    vector<long long> cards = readList(n);
    cout << getCardCount(n, k, cards);
}
