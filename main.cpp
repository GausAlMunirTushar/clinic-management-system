
// File: main.cpp
#include "./src/auth.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    Authentication auth;
    bool isLoggedIn = false;
    string loggedInUser;
    int choice;

    do {
        if (!isLoggedIn) {
            cout << "\n--- Clinic Management System ---\n";
            cout << "1. Register\n2. Login\n0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (auth.registerUser(username, password)) {
                    cout << "Registration successful!\n";
                } else {
                    cout << "Registration failed!\n";
                }
                break;
            }
            case 2: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (auth.loginUser(username, password)) {
                    isLoggedIn = true;
                    loggedInUser = username;
                    cout << "Login successful! Welcome, " << username << "!\n";
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
            }
        } else {
            cout << "\n--- Main Menu ---\n";
            cout << "1. Add Doctor\n2. View Doctors\n3. Add Patient\n4. View Patients\n5. Logout\n0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "[Add Doctor functionality here]" << endl;
                break;
            case 2:
                cout << "[View Doctors functionality here]" << endl;
                break;
            case 3:
                cout << "[Add Patient functionality here]" << endl;
                break;
            case 4:
                cout << "[View Patients functionality here]" << endl;
                break;
            case 5:
                isLoggedIn = false;
                loggedInUser = "";
                cout << "Logged out successfully!\n";
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
            }
        }
    } while (choice != 0);

    return 0;
}
