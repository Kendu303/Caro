#include "part1.h"
#include "part2.h"
#include <fstream>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

void runPart1() {
    List* ll = CreateList();
    if (!ReadListFromFile(ll, "input.txt")) {
        cout << "Khong the doc duoc danh sach lien ket" << endl;
        return;
    }

    int choice = 0;
    while (true) {
        cout << endl << "===== PART 1 =====" << endl;
        cout << "1. Them n phan tu vao danh sach" << endl;
        cout << "2. Tinh tong cac so chinh phuong" << endl;
        cout << "3. Tach thanh 2 danh sach chan le" << endl;
        cout << "0. Tro ve menu chinh" << endl;
        cout << endl << "Vui long nhap lua chon cua ban: ";
        cin >> choice;

        if (choice == 1) {
            int n;
            cout << "Nhap so luong phan tu: ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                int x;
                cout << "Nhap phan tu thu " << i + 1 << ": ";
                cin >> x;
                AddTail(ll, x);
            }
            cout << "Danh sach hien tai: ";
            PrintList(ll);
        }
        else if (choice == 2) {
            cout << "Tong cac so can bac 2 hoan hao: " << PerfectSquareSum(ll) << endl;
        }
        else if (choice == 3) {
            List* oddList = SplitOdd(ll);
            List* evenList = SplitEven(ll);
            cout << "Danh sach le: ";
            PrintList(oddList);
            cout << "Danh sach chan: ";
            PrintList(evenList);
        }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "Lua chon khong hop le" << endl;
        }
    }
}

void runPart2() {
    ProductList* products = ReadProducts("input.txt");
    if (!products) {
        cout << "Khong the doc duoc file input.txt / Dinh dang cua file input.txt khong dung!" << endl;
        return;
    }

    int choice = 0;
    while (true) {
        cout << endl << "===== PART 2 =====" << endl;
        cout << "1. Hien thi danh sach san pham" << endl;
        cout << "2. Tim san pham Apple" << endl;
        cout << "3. Tinh tong gia san pham Milk" << endl;
        cout << "0. Tro ve menu chinh" << endl;
        cout << endl << "Vui long nhap lua chon cua ban: ";
        cin >> choice;

        if (choice == 1) {
            DisplayProducts(products);
        }
        else if (choice == 2) {
            cout << "Cac san pham Apple:" << endl;
            FindAppleProducts(products);
        }
        else if (choice == 3) {
            cout << "Tong gia san pham Milk: " << fixed << setprecision(2)
                << CalculateMilkTotal(products) << endl;
        }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "Lua chon khong hop le" << endl;
        }
    }
}

int main() {
    int choice = 0;
    while (true) {
        cout << endl << "===== MENU =====" << endl;
        cout << "1. Part 1: Singly Linked List" << endl;
        cout << "2. Part 2: File Handling" << endl;
        cout << "0. Thoat" << endl;
        cout << endl << "Vui long nhap lua chon cua ban: ";
        cin >> choice;

        if (choice == 1) {
            runPart1();
        }
        else if (choice == 2) {
            runPart2();
        }
        else if (choice == 0) {
            cout << endl << "Thoat program..." << endl;
            break;
        }
        else {
            cout << "Lua chon khong hop le!" << endl;
        }
    }
    return 0;
}