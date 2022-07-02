// В этой задаче требуется сделать разворот части односвязного списка.
// Каждая вершина списка описывается структурой Node, каждый экземпляр хранит указатель на следующую вершину или nullptr, если вершина последняя.
// По заданным индексам from и to разверните все вершины на отрезке с from до to включительно.
// Заметьте, что нумерация в индексах from и to с единицы.

// Формат ввода
// Реализуйте функцию Reverse, которая принимает голову списка и два целочисленных индекса.
// Гарантируется, что в списке есть хотя бы одна вершина.
// Суммарное число вершин не превосходит 10^5.

// Формат вывода
// Функция Reverse должна возвращать голову изменённого списка. Создавать вершины заново нельзя.

using namespace std;

/**
struct Node {
    int val;
    Node* next;
    Node(int val_, Node* next_) {
        val = val_;
        next = next_;
    }
};
**/


Node* Reverse(Node* head, int left, int right) {
    if (left >= right)
    {
        return head;
    }
    Node ghostHead(0, head);
    Node* curr = &ghostHead;
    while ((curr->next != nullptr) && (curr->next->val != left))
    {
        curr = curr->next;
    }
    Node* beforeBegin = curr;
    Node* begin = curr->next;
    curr = begin;
    Node* prev = nullptr;
    Node* next = nullptr;
    while ((curr->next != nullptr) && (curr->val != right))
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    // curr is end
    begin->next = curr->next;
    curr->next = prev;
    beforeBegin->next = curr;
    return ghostHead.next;
}
