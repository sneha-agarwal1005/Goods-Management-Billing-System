#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "auth.h"
#include "product.h"
#include "billing.h"
using namespace std;

// MAIN MENU
int menu1() {
    int ch;
    while (1) {
        cout << "\n1. Goods\n2. Billing\n3. Exit\nENTER CHOICE: ";
        cin >> ch;

        if (ch == 1) menu();
        else if (ch == 2) billing();
        else if (ch == 3) return 0;
    }
}

// MAIN
int main() {
    int loggedIn = 0, choice;
    cout << "\n==========================================\n";
    cout << "              WELCOME TO JCH \n";
    cout << "     GOODS MANAGEMENT & BILLING SYSTEM\n";
    cout << "==========================================\n";
        
    while (1) {
        if (!loggedIn) {
            cout << "\n1. Login\n2. Exit\nENTER CHOICE: ";
            cin >> choice;
            cin.get();  
            if (choice == 1) {
                if (login()) {
                    loggedIn = 1;
                    cout << "Login successful!\n";
                    cout << "==========================================\n";
                }
            } else return 0;
        }

        if (loggedIn) {
            menu1();
            cout << "==========================================\n";
            cout << "\n1. Logout\n2. Exit\nENTER CHOICE: ";
            cin >> choice;
            cin.get();  

            if (choice == 1) {
                logout();
                loggedIn = 0;
            } else return 0;
        }
    }
} 