#include "part1.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

Note* CreateNote(int v) {
    Note* node = new Note;
    node->data = v;
    node->next = nullptr;
    return node;
}

List* CreateList() {
    List* ll = new List;
    ll->pHead = nullptr;
    return ll;
}

void AddTail(List* ll, int v) {
    Note* node = CreateNote(v);
    if (ll->pHead == nullptr) {
        ll->pHead = node;
        return;
    }
    Note* current = ll->pHead;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = node;
}

void PrintList(List* ll) {
    for (Note* p = ll->pHead; p != nullptr; p = p->next) {
        cout << p->data << " ";
    }
    cout << endl;
}

bool isPerfectSquare(int n) {
    if (n < 0) return false;
    int root = sqrt(n);
    return root * root == n;
}

int PerfectSquareSum(List* ll) {
    int sum = 0;
    for (Note* p = ll->pHead; p != nullptr; p = p->next) {
        if (isPerfectSquare(p->data)) {
            sum += p->data;
        }
    }
    return sum;
}

List* SplitOdd(List* ll) {
    List* oddList = CreateList();
    for (Note* p = ll->pHead; p != nullptr; p = p->next) {
        if (p->data % 2 != 0) {
            AddTail(oddList, p->data);
        }
    }
    return oddList;
}

List* SplitEven(List* ll) {
    List* evenList = CreateList();
    for (Note* p = ll->pHead; p != nullptr; p = p->next) {
        if (p->data % 2 == 0) {
            AddTail(evenList, p->data);
        }
    }
    return evenList;
}

bool ReadListFromFile(List* ll, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    int value;
    while (file >> value) {
        AddTail(ll, value);
    }

    file.close();
    return true;
}