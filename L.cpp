// Вам даны две последовательности отрезков. Каждый отрезок задаётся координатой начала и конца — (start[i], end[i]).
// Отрезки каждой последовательности отсортированы слева направо и не имеют общих точек.
// Найдите пересечение двух последовательностей отрезков. То есть третью последовательность отрезков, такую, что:
// 1. Каждый отрезок содержится в некотором отрезке и первой, и второй последовательности;
// 2. Никакой отрезок нельзя увеличить;
// 3. Отрезки этой последовательности не имеют общих точек;
// 4. Отрезки в последовательности также отсортированы в порядке возрастания.

// Формат ввода
// В первой строке дано число отрезков в первой последовательности n (0 ≤ n ≤ 100000)
// В следующих n строках даны отрезки первой последовательности по одному на строке. 
// Каждый отрезок записан в формате start[i] end[i],
// координаты начала и конца целые неотрицательные числа, не превосходящие по модулю 10^9.
// В строке n + 2 дана длина второй последовательности m, (0 ≤ m ≤ 100000).
// В следующих m строках заданы отрезки второй последовательности.
// Гарантируется, что end[i] < start[i + 1], а также что end[i] − start[i] > 0.

// Формат вывода
// Выведите по одному в строке отсортированные отрезки из пересечения последовательностей в том же формате, что и во входных данных.
// Заметьте, что длина отрезков в пересечении может быть нулевой, в этом случае start[i] = end[i].
#include <iostream>
#include <vector>

using namespace std;

struct Segment {
    int left;
    int right;

    Segment(int left, int right) : left(left), right(right) {
    }
};

vector<Segment> readSegments() {
    int n;
    cin >> n;
    vector<Segment> segments;
    for (int i = 0; i < n; ++i) {
        int left, right;
        cin >> left >> right;
        segments.emplace_back(left, right);
    }
    return segments;
}
    
vector<Segment> getIntersection(const vector<Segment>& firstSequence, const vector<Segment>& secondSequence) {
    vector<Segment> result;
    int firstIdx = 0;
    int secondIdx = 0;
    while ((firstIdx < firstSequence.size()) && (secondIdx < secondSequence.size()))
    {
        Segment intersection(std::max(firstSequence[firstIdx].left, secondSequence[secondIdx].left),
                             std::min(firstSequence[firstIdx].right, secondSequence[secondIdx].right));
        if (intersection.left <= intersection.right)
        {
            result.emplace_back(intersection.left, intersection.right);
        }
        if (firstSequence[firstIdx].right == intersection.right)
        {
            ++firstIdx;
        }
        if (secondSequence[secondIdx].right == intersection.right)
        {
            ++secondIdx;
        }
    }
    return result;
}


void outputAnswer(const vector<Segment>& intersection) {
    for (const Segment& segment : intersection) {
        cout << segment.left << " " << segment.right << endl;
    }
}

int main() {
    vector<Segment> firstSequence = readSegments();
    vector<Segment> secondSequence = readSegments();

    vector<Segment> intersection = getIntersection(firstSequence, secondSequence);
    outputAnswer(intersection);
}
