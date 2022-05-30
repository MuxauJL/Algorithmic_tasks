// Вам дана матрица из n строк и m столбцов, заполненная натуральными числами.
// По матрице можно перемещаться, из клетки можно уходить только в соседнюю по стороне клетку,
// переходы по диагонали, а также выход за границу матрицы запрещены.
// Ваша задача — найти наиболее длинный возрастающий путь в матрице.
// Путь возрастающий, если значения в посещаемых клетках строго возрастают от начала пути к его концу.

// Формат ввода
// В первой строке даны два числа, описывающие размер матрицы — n, m (1 ≤ n, m ≤ 10^3).
// В следующих n строках записана сама матрица. 
// i-я строка матрицы содержит m чисел, записанных через пробел.
// Все элементы матрицы — натуральные числа, не превосходящие 10^9.

// Формат вывода
// Выведите единственное число — длину наибольшего возрастающего пути.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Cell
{
    int row;
    int col;
    Cell(int row, int col)
        :row(row), col(col)
    {}
};

std::vector<Cell> neighbors = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};


int findLongestPath(int n, int m, const vector<vector<int>>& matrix, 
                    vector<vector<int>>& cache, Cell prev, Cell curr)
{
    if (cache[curr.row][curr.col] > 0)
    {
        return cache[curr.row][curr.col];
    }
    int longest = 1;
    for (const auto& dir: neighbors)
    {
        Cell neighbor(curr.row + dir.row, curr.col + dir.col);
        if (((neighbor.row != prev.row) || (neighbor.col != prev.col)) &&
            (neighbor.row >= 0) &&
            (neighbor.row < n) &&
            (neighbor.col >= 0) &&
            (neighbor.col < m) &&
            (matrix[curr.row][curr.col] < matrix[neighbor.row][neighbor.col]))
        {
            if (cache[neighbor.row][neighbor.col] > 0)
            {
                longest = std::max(longest, 1 + cache[neighbor.row][neighbor.col]);
            }
            else
            {
                longest = std::max(longest, 1 + findLongestPath(n, m, matrix,
                                                                cache, curr, neighbor));
            }
        }
    }
    cache[curr.row][curr.col] = longest;
    return longest;
}

int getLongestIncreasingPath(int n, int m, const vector<vector<int>>& matrix) {
    // your code goes here
    vector<vector<int>> cache(n, vector<int>(m, 0));
    int longest = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            longest = std::max(longest, findLongestPath(n, m, matrix,
                                                        cache, Cell(i, j), Cell(i, j)));
        }
    }
    
    return longest;
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

vector<vector<int>> readMatrix(int n, int m) {
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        matrix[i] = readList(m);
    }
    return matrix;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix = readMatrix(n, m);
    cout << getLongestIncreasingPath(n, m, matrix);
}
