#include "part2.h"
#include <fstream>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

ProductList* CreateProductList() {
    ProductList* list = new ProductList;
    list->head = nullptr;
    return list;
}

void AddTail(ProductList* list, const char* id, const char* name, double price, const char* expDate) {
    Product* product = new Product;
    strcpy(product->id, id);
    strcpy(product->name, name);
    strcpy(product->expDate, expDate);
    product->price = price;
    product->next = nullptr;

    if (list->head == nullptr) {
        list->head = product;
        return;
    }

    Product* current = list->head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = product;
}

ProductList* ReadProducts(const char* filename) {
    ProductList* list = CreateProductList();
    ifstream file(filename);
    if (!file.is_open()) return nullptr;

    char line[256];
    while (file.getline(line, 256)) {
        char id[20], name[50], expDate[20];
        double price;

        char* token = strtok(line, "-");
        if (!token) continue;
        strcpy(id, token);

        token = strtok(nullptr, "-");
        if (!token) continue;
        strcpy(name, token);

        token = strtok(nullptr, "-");
        if (!token) continue;
        price = atof(token);

        token = strtok(nullptr, "-");
        if (!token) continue;

        char year[5], month[3], day[3];
        strncpy(year, token, 4);
        year[4] = '\0';
        strncpy(month, token + 5, 2);
        month[2] = '\0';
        strncpy(day, token + 8, 2);
        day[2] = '\0';
        sprintf(expDate, "%s/%s/%s", day, month, year);

        AddTail(list, id, name, price, expDate);
    }
    file.close();
    return list;
}

void DisplayProducts(ProductList* list) {
    for (Product* p = list->head; p != nullptr; p = p->next) {
        cout << "Product ID: " << p->id << ", Name: " << p->name
            << ", Price: " << fixed << setprecision(2) << p->price
            << ", Expiration Date: " << p->expDate << endl;
    }
}

void FindAppleProducts(ProductList* list) {
    for (Product* p = list->head; p != nullptr; p = p->next) {
        if (strstr(p->name, "Apple") != nullptr) {
            char day[3], month[3], year[5];
            strncpy(day, p->expDate, 2);
            day[2] = '\0';
            strncpy(month, p->expDate + 3, 2);
            month[2] = '\0';
            strncpy(year, p->expDate + 6, 4);
            year[4] = '\0';

            cout << p->id << "-" << p->name << "-" << fixed << setprecision(1)
                << p->price << "-" << year << "-" << month << "-" << day << endl;
        }
    }
}

double CalculateMilkTotal(ProductList* list) {
    double total = 0;
    for (Product* p = list->head; p != nullptr; p = p->next) {
        if (strstr(p->name, "Milk") != nullptr) {
            total += p->price;
        }
    }
    return total;
}