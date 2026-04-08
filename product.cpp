#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "product.h"
using namespace std;

#define PRODUCT_FILE "product.dat"

void clearBuffer() {
    int c;
    while ((c = cin.get()) != '\n' && c != EOF);
}

int menu() {
    int choice;
    do {
        cout << "\n-------------Goods Management System ----------------------\n";
        cout << "1. Add Product\n2. View Products\n3. Search Product\n";
        cout << "4. Update Product\n5. Delete Product\n6. Calculate Stock\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: calculateStock(); break;
            case 7: return 0;
            default: cout << "Invalid choice!\n";
        }
    } while (choice <= 7);

    return 0;
}

// ADD PRODUCT
void addProduct() {
    FILE *file = fopen(PRODUCT_FILE, "a");
    if (!file) return;

    Product product;

    cout << "Enter Product ID: ";
    cin >> product.id;
    clearBuffer();

    cout << "Enter Product Name: ";
    cin.getline(product.name, sizeof(product.name));

    cout << "Enter Quantity: ";
    cin >> product.quantity;

    cout << "Enter Price: ";
    cin >> product.price;

    fwrite(&product, sizeof(Product), 1, file);
    fclose(file);

    cout << "Product added successfully!\n";
}

// VIEW PRODUCTS
void viewProducts() {
    FILE *file = fopen(PRODUCT_FILE, "r");
    if (!file) return;

    Product product;

    cout << "\nID\tName\tQuantity\tPrice\n";

    while (fread(&product, sizeof(Product), 1, file)) {
        cout << product.id << "\t"
             << product.name << "\t"
             << product.quantity << "\t\t"
             << product.price << "\n";
    }

    fclose(file);
}

// SEARCH PRODUCT
void searchProduct() {
    FILE *file = fopen(PRODUCT_FILE, "r");
    if (!file) return;

    int id;
    cout << "Enter Product ID: ";
    cin >> id;

    Product product;
    int found = 0;

    while (fread(&product, sizeof(Product), 1, file)) {
        if (product.id == id) {
            cout << "Found: " << product.name
                 << " | Qty: " << product.quantity
                 << " | Price: " << product.price << "\n";
            found = 1;
            break;
        }
    }

    if (!found) cout << "Not found!\n";

    fclose(file);
}

// UPDATE
void updateProduct() {
    FILE *file = fopen(PRODUCT_FILE, "r+");
    if (!file) return;

    int id;
    cout << "Enter Product ID: ";
    cin >> id;

    Product product;
    int found = 0;

    while (fread(&product, sizeof(Product), 1, file)) {
        if (product.id == id) {
            cout << "Enter new Quantity: ";
            cin >> product.quantity;

            cout << "Enter new Price: ";
            cin >> product.price;

            fseek(file, -sizeof(Product), SEEK_CUR);
            fwrite(&product, sizeof(Product), 1, file);

            found = 1;
            break;
        }
    }

    if (!found) cout << "Not found!\n";

    fclose(file);
}

// DELETE
void deleteProduct() {
    FILE *file = fopen(PRODUCT_FILE, "r");
    FILE *temp = fopen("temp.dat", "w");

    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    Product p;
    int found = 0;

    while (fread(&p, sizeof(Product), 1, file)) {
        if (p.id != id)
            fwrite(&p, sizeof(Product), 1, temp);
        else
            found = 1;
    }

    fclose(file);
    fclose(temp);

    remove(PRODUCT_FILE);
    rename("temp.dat", PRODUCT_FILE);

    if (found) cout << "Deleted!\n";
    else cout << "Not found!\n";
}

// STOCK
void calculateStock() {
    FILE *file = fopen(PRODUCT_FILE, "r");
    if (!file) return;

    Product p;
    int total = 0;
    float value = 0;

    while (fread(&p, sizeof(Product), 1, file)) {
        total += p.quantity;
        value += p.quantity * p.price;
    }

    cout << "Total Items: " << total << "\n";
    cout << "Total Value: " << value << "\n";

    fclose(file);
}