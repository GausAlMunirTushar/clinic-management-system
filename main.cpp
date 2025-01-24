#include "./src/auth.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Doctor {
    int id;
    string name;
    string specialization;
};

struct Patient {
    int id;
    string name;
    int age;
    double height; // in meters
    double weight; // in kg
};

vector<Doctor> doctors;
vector<Patient> patients;
int doctorID = 1;
int patientID = 1;

void clearScreen() {
    cout << string(50, '\n');
}

void showBanner(const string& title) {
    cout << "\n===================================\n";
    cout << "         " << title << "         \n";
    cout << "===================================\n\n";
}

void addDoctor() {
    Doctor doc;
    doc.id = doctorID++;
    cout << "Enter doctor's name: ";
    cin.ignore();
    getline(cin, doc.name);
    cout << "Enter specialization: ";
    getline(cin, doc.specialization);
    doctors.push_back(doc);
    cout << "\nDoctor added successfully!\n";
}

void viewDoctors() {
    if (doctors.empty()) {
        cout << "\nNo doctors available.\n";
        return;
    }
    showBanner("Doctor List");
    cout << left << setw(5) << "ID" << setw(20) << "Name" << "Specialization\n";
    cout << "-------------------------------------\n";
    for (const auto& doc : doctors) {
        cout << left << setw(5) << doc.id << setw(20) << doc.name << doc.specialization << "\n";
    }
}

void deleteDoctor() {
    viewDoctors();
    if (doctors.empty()) return;

    int id;
    cout << "\nEnter Doctor ID to delete: ";
    cin >> id;

    auto it = find_if(doctors.begin(), doctors.end(), [id](const Doctor& doc) {
        return doc.id == id;
    });

    if (it != doctors.end()) {
        doctors.erase(it);
        cout << "\nDoctor deleted successfully!\n";
    } else {
        cout << "\nDoctor not found!\n";
    }
}

void addPatient() {
    Patient pat;
    pat.id = patientID++;
    cout << "Enter patient's name: ";
    cin.ignore();
    getline(cin, pat.name);
    cout << "Enter age: ";
    cin >> pat.age;
    cout << "Enter height (in meters): ";
    cin >> pat.height;
    cout << "Enter weight (in kg): ";
    cin >> pat.weight;
    patients.push_back(pat);
    cout << "\nPatient added successfully!\n";
}

void viewPatients() {
    if (patients.empty()) {
        cout << "\nNo patients available.\n";
        return;
    }
    showBanner("Patient List");
    cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(5) << "Age" << "BMI\n";
    cout << "-------------------------------------\n";
    for (const auto& pat : patients) {
        double bmi = pat.weight / (pat.height * pat.height);
        cout << left << setw(5) << pat.id << setw(20) << pat.name << setw(5) << pat.age << fixed << setprecision(2) << "\n";
    }
}

void deletePatient() {
    viewPatients();
    if (patients.empty()) return;

    int id;
    cout << "\nEnter Patient ID to delete: ";
    cin >> id;

    auto it = find_if(patients.begin(), patients.end(), [id](const Patient& pat) {
        return pat.id == id;
    });

    if (it != patients.end()) {
        patients.erase(it);
        cout << "\nPatient deleted successfully!\n";
    } else {
        cout << "\nPatient not found!\n";
    }
}

int main() {
    Authentication auth;
    bool isLoggedIn = false;
    int choice;

    do {
        if (!isLoggedIn) {
            showBanner("Clinic Management System");
            cout << "1. Register\n2. Login\n0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                string username;
                cout << "Enter username: ";
                cin >> username;
                string password = auth.inputPassword();
                if (auth.registerUser(username, password)) {
                    cout << "\nRegistration successful!\n";
                } else {
                    cout << "\nRegistration failed!\n";
                }
                break;
            }
            case 2: {
                string username;
                cout << "Enter username: ";
                cin >> username;
                string password = auth.inputPassword();
                if (auth.loginUser(username, password)) {
                    isLoggedIn = true;
                    cout << "\nLogin successful! Welcome, " << username << "!\n";
                } else {
                    cout << "\nInvalid credentials!\n";
                }
                break;
            }
            case 0:
                cout << "\nExiting...\n";
                break;
            default:
                cout << "\nInvalid choice!\n";
            }
        } else {
            showBanner("Main Menu");
            cout << "1. Add Doctor\n2. View Doctors\n3. Delete Doctor\n4. Add Patient\n5. View Patients\n6. Delete Patient\n7. Logout \n0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addDoctor();
                break;
            case 2:
                viewDoctors();
                break;
            case 3:
                deleteDoctor();
                break;
            case 4:
                addPatient();
                break;
            case 5:
                viewPatients();
                break;
            case 6:
                deletePatient();
                break;
            case 7:
                isLoggedIn = false;
                cout << "\nLogged out successfully!\n";
                break;
            case 0:
                cout << "\nExiting...\n";
                break;
            default:
                cout << "\nInvalid choice!\n";
            }
        }
    } while (choice != 0);

    return 0;
}
