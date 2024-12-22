#ifndef PART1_H
#define PART1_H

struct Note {
    int data;
    Note* next;
};

struct List {
    Note* pHead;
};

Note* CreateNote(int v);
List* CreateList();
void AddTail(List* ll, int v);
void PrintList(List* ll);
int PerfectSquareSum(List* ll);
List* SplitOdd(List* ll);
List* SplitEven(List* ll);
bool ReadListFromFile(List* ll, const char* filename);

#endif