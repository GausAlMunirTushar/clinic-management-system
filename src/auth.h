#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <iomanip>

using namespace std;

class Authentication {
public:
    bool registerUser(const string& username, const string& password) {
        ofstream file("data/users.txt", ios::app);
        if (file.is_open()) {
            file << username << "," << encryptPassword(password) << endl;
            file.close();
            return true;
        }
        return false;
    }

    bool loginUser(const string& username, const string& password) {
        ifstream file("data/users.txt");
        string line, storedUsername, storedPassword;
        if (file.is_open()) {
            while (getline(file, line)) {
                size_t delimiterPos = line.find(",");
                storedUsername = line.substr(0, delimiterPos);
                storedPassword = line.substr(delimiterPos + 1);

                if (storedUsername == username && decryptPassword(storedPassword) == password) {
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    string inputPassword() {
        string password;
        char ch;
        cout << "Enter password: ";
        while ((ch = _getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b' && !password.empty()) { // Handle backspace
                cout << "\b \b";
                password.pop_back();
            } else if (ch != '\b') {
                password.push_back(ch);
                cout << "*";
            }
        }
        cout << endl;
        return password;
    }

private:
    string encryptPassword(const string& password) {
        string encrypted = password;
        for (char& c : encrypted) {
            c += 3; // Simple Caesar cipher for demonstration
        }
        return encrypted;
    }

    string decryptPassword(const string& encrypted) {
        string decrypted = encrypted;
        for (char& c : decrypted) {
            c -= 3;
        }
        return decrypted;
    }
};

#endif // AUTH_H
