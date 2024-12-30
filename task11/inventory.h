#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

struct Product {
    union {
        char name[50];
        int id;
    };
    int quantity;
    double price;
    char date[11];
};

Product* createInventory(int* size, const char* targetProduct);
void viewInventory(Product* inventory, int size);
Product* addProducts(Product* inventory, int* size);
void searchProduct(Product* inventory, int size, double minPrice);
void deleteProduct(Product* inventory, int* size, const char* name);
void modifyProduct(Product* inventory, int size, const char* name);
void sortInventory(Product* inventory, int size);
void saveToFile(Product* inventory, int size);
void loadFromFile(Product** inventory, int* size);
void modifyProductInFile(const char* name);
Product* modaddProduct(Product* inventory, int* size);
void findAndDisplayProduct(Product* inventory, int size, const char* name);

#endif
