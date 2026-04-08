#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "auth.h"
using namespace std;

#define MAX_TRIES 3

#define PRODUCT_FILE "products.dat"
#define BILL_FILE "bills.dat"

// AUTHENTICATION
const char predefined_username[] = "ADMIN";
const char predefined_password[] = "JCH123";

int login() {
    char username[50], password[50];
    int attempts = 0;

    while (attempts < MAX_TRIES) {
        cout << "\nEnter username: ";
        cin.getline(username, sizeof(username));

        cout << "Enter password: ";
        cin.getline(password, sizeof(password));

        if (strcmp(username, predefined_username) == 0 &&
            strcmp(password, predefined_password) == 0) {
            return 1;
        } else {
            cout << "Invalid username or password. Try again.\n";
            attempts++;
        }
    }
    return 0;
}

void logout() {
    cout << "\nYou have successfully logged out.\n";
    cout << "\nTHANK YOU FOR VISITING\n";
    cout << "==========================================\n";
}