#ifndef PRODUCT_H
#define PRODUCT_H

struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
};

void addProduct();
void viewProducts();
void searchProduct();
void updateProduct();
void deleteProduct();
void calculateStock();
int menu();

#endif