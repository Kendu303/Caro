#ifndef PART2_H
#define PART2_H

struct Product {
    char id[20];
    char name[50];
    double price;
    char expDate[20];
    Product* next;
};

struct ProductList {
    Product* head;
};

ProductList* CreateProductList();
void AddTail(ProductList* list, const char* id, const char* name, double price, const char* expDate);
ProductList* ReadProducts(const char* filename);
void DisplayProducts(ProductList* list);
void FindAppleProducts(ProductList* list);
double CalculateMilkTotal(ProductList* list);

#endif