#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <limits>
#include "product.h"
#include "billing.h"
using namespace std;

#define PRODUCT_FILE "product.dat"
#define BILL_FILE "bill.dat"

struct Bill {
    int bill_id;
    char customer_name[50];
    char customer_phone[20];
    char date[20];
    char time[20];
    int product_ids[10];
    char product_names[10][50];
    int product_quantities[10];
    float product_prices[10];
    int product_count;
    float total_amount;
};
//VALIDATE INPUT(PHONE NO)

void getValidPhone(char phone[]) {
    while (true) {
        cin.getline(phone, 20);

        int len = strlen(phone);
        int valid = 1;

        if (len != 10) valid = 0;

        for (int i = 0; i < len; i++) {
            if (!isdigit(phone[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            cout << "Invalid phone! Enter 10-digit number: ";
        } else {
            break;
        }
    }
}

//VALIDATING QUANTITY
int getValidQuantity() {
    int qty;

    cout << "Enter quantity: ";

    while (!(cin >> qty) || qty <= 0) {
        cout << "Invalid input! Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    return qty;
}

void billing() {
    int i;
    cout << "\n1. Create Bill\n2. View Bill\nEnter Choice: ";
    cin >> i;

    if (i == 1) createBill();
    else if (i == 2) viewBills();
    else cout << "Invalid choice";
}

void createBill() {
    FILE *pf = fopen(PRODUCT_FILE, "r+");
    FILE *bf = fopen(BILL_FILE, "a");

    if (!pf || !bf) return;

    Bill bill;

    cout << "Enter Bill ID: ";
    cin >> bill.bill_id;
    cin.ignore();
    cout << "Enter Customer Name: ";
    cin.getline(bill.customer_name, sizeof(bill.customer_name));

    cout << "Enter Phone: ";
    getValidPhone(bill.customer_phone);

    bill.product_count = 0;
    bill.total_amount = 0;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    snprintf(bill.date, sizeof(bill.date), "%02d/%02d/%04d",ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);

    snprintf(bill.time, sizeof(bill.time), "%02d:%02d:%02d",ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    bill.product_count = 0;
    bill.total_amount = 0;

    char ch;

    do {
        int id, qty;
        Product p;

        cout << "Enter Product ID: ";
        cin >> id;

        qty = getValidQuantity();

        rewind(pf);
        int found = 0;

        while (fread(&p, sizeof(Product), 1, pf)) {
            if (p.id == id) {
                if (p.quantity >= qty) {
                    int i = bill.product_count;
                    bill.product_ids[i] = id;
                    strcpy(bill.product_names[i], p.name);
                    bill.product_quantities[i] = qty;
                    bill.product_prices[i] = p.price;
                    bill.product_count++;

                    bill.total_amount += p.price * qty;

                    p.quantity -= qty;
                    fseek(pf, -sizeof(Product), SEEK_CUR);
                    fwrite(&p, sizeof(Product), 1, pf);
                }
                found = 1;
                break;
            }
        }

        if (!found) cout << "Product not found!\n";

        cout << "Add more? (y/n): ";
        cin >> ch;

    } while ((ch == 'y' || ch == 'Y') && bill.product_count < 10);

    fwrite(&bill, sizeof(Bill), 1, bf);

    cout << "Total Amount: " << bill.total_amount << "\n";

    fclose(pf);
    fclose(bf);
}

// VIEW BILLS
void viewBills() {
    FILE *file = fopen(BILL_FILE, "r");
    if (!file) return;

    Bill b;

    while (fread(&b, sizeof(Bill), 1, file)) 
    {
        cout << "\n==========================================\n";
        cout << "              INVOICE\n";
        cout << "==========================================\n";
        
        cout << "Bill ID   : " << b.bill_id << "\n";
        cout << "Customer  : " << b.customer_name << "\n";
        cout << "Phone     : " << b.customer_phone << "\n";
        cout << "Date      : " << b.date << "\n";
        cout << "Time      : " << b.time << "\n";
        
        cout << "------------------------------------------\n";
        cout << "ID    Name            Qty   Price   Total\n";
        cout << "------------------------------------------\n";
        
        for (int i = 0; i < b.product_count; i++) 
        {
            float item_total = b.product_quantities[i] * b.product_prices[i];
        
            cout << b.product_ids[i] << "     "
                 << b.product_names[i] << "     "
                 << b.product_quantities[i] << "     "
                 << b.product_prices[i] << "     "
                 << item_total << "\n";
        }
        
        cout << "------------------------------------------\n";
        cout << "Grand Total: " << b.total_amount << "\n";
        cout << "==========================================\n";
    }

    fclose(file);
}