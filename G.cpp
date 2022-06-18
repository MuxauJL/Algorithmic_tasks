// Дано укоренённое дерево на N вершинах и число X.
// В каждой вершине записано число — её вес.
// Назовём восходящим путь a, p(a), p(p(a)), ..., где p(a) — родитель вершины a.
// Проще говоря, восходящий путь — это путь, который начинается с некоторой вершины и двигается в сторону корня (не обязательно доходя до него).
// Путь может состоять из одной вершины.
// Весом пути назовём суммарный вес вершин на этом пути.
// Найдите количество восходящих путей с весом X.

// Формат ввода
// В первой строке дано число вершин n(1 ≤ n ≤ 2 ⋅ 10^5) и число X(−10^9 ≤ X ≤ 10^9).
// В следующих n строках по одной в строке заданы вершины. 
// i-я вершина задаётся двумя числами — p[i] и w[i], записанными через пробел.
// p[i] — это либо номер вершины-родителя вершины i, в этом случае 0 ≤ p[i] ≤ n − 1, либо −1, если вершина i является корнем.
// w[i] — это вес вершины i(−10^4 ≤ w[i] ≤ 10^4).

// Формат вывода
// Выведите одно целое число — количество восходящих путей веса X.

#include <vector>
#include <set>
#include <iostream>

using namespace std;

struct Vertex {
    int w;
    int p;

    Vertex(int w, int p)
    :w(w), p(p)
    {
    }
};

struct PathVertex {
    int id;
    int w;

    PathVertex(int id, int w)
    :id(id), w(w)
    {
    }
};

vector<bool> getLeavesMask(const vector<Vertex>& tree)
{
    vector<bool> leavesMask(tree.size(), true);
    for (int i = 0; i < tree.size(); ++i)
    {
        if (tree[i].p != -1)
        {
            leavesMask[tree[i].p] = false;
        }
    }
    return leavesMask;
}

std::vector<PathVertex> findUpgoingPathLengthsFromVertex(int id, const vector<Vertex>& tree, int x)
{
    std::vector<PathVertex> path;
    path.reserve(tree.size());
    path.emplace_back(id, tree[id].w);
    int parentId = tree[id].p;
    while (parentId != -1)
    {
        path.emplace_back(parentId, tree[parentId].w);
        parentId = tree[parentId].p;
    }
    return path;
}

void addPaths(const vector<PathVertex>& path, int x, set<pair<int, int>>& paths)
{
    if (path.empty() || x == 0)
    {
        return;
    }
    int left = 0;
    int right = 1;
    int length = path[left].w;
    while (right < path.size())
    {
        if (length < x)
        {
            length += path[right++].w;
        }
        else
        {
            if (length == x)
            {
                paths.emplace(path[left].id, path[right - 1].id);
            }
            length -= path[left++].w;
        }
        right = max(right, left + 1);
    }
    while ((length >= x) && (left < path.size()))
    {
        if (length == x)
        {
            paths.emplace(path[left].id, path[right - 1].id);
        }
        length -= path[left++].w;
    }
}

int getNumberOfUpgoingPaths(const vector<Vertex>& tree, int x) {
    vector<bool> leavesMask = getLeavesMask(tree);
    set<pair<int, int>> paths;
    for (int i = 0; i < tree.size(); ++i)
    {
        if (leavesMask[i])
        {
            vector<PathVertex> path = findUpgoingPathLengthsFromVertex(i, tree, x);
            addPaths(path, x, paths);
        }
    }
    return paths.size();
}

vector<Vertex> readTree(int n) {
    vector<Vertex> tree;
    for (int i = 0; i < n; ++i) {
        int parent, weight;
        cin >> parent >> weight;
        tree.emplace_back(weight, parent);
    }
    return tree;
}

int main() {
    int n;
    cin >> n;
    int x;
    cin >> x;
    vector<Vertex> tree = readTree(n);
    cout << getNumberOfUpgoingPaths(tree, x);

}
