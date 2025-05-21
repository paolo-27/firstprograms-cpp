#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Debt {
    string name;
    double amount;
    string dueDate; 
};

// Utility: Split a line by delimiter
vector<string> splitCSVLine(const string& line) {
    vector<string> result;
    istringstream ss(line);
    string item;
    while (getline(ss, item)) {
        result.push_back(item);
    }
    return result;
}

// Save debts to file
void saveToFile(const vector<Debt>& debts, const string& filename) {
    ofstream file(filename);
    for (const auto& d : debts) {
        file << d.name << "," << d.amount << "," << d.dueDate << "\n";
    }
    file.close();
}

// Load debts from file
void loadFromFile(vector<Debt>& debts, const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<string> parts = splitCSVLine(line);
        if (parts.size() == 3) {
            string name = parts[0];
            double amount = stod(parts[1]);
            string dueDate = parts[2];
            debts.push_back({ name, amount, dueDate });
        }
    }
    file.close();
}

// Sort debts by due date
void sortDebts(vector<Debt>& debts) {
    sort(debts.begin(), debts.end(), [](const Debt& a, const Debt& b) {
        return a.dueDate < b.dueDate;
    });
}

// Display all debts
void showDebts(const vector<Debt>& debts) {
    cout << "\nDebts List:\n";
    for (const auto& d : debts) {
        cout << "Name: " << d.name << ", Amount: " << d.amount << ", Due: " << d.dueDate << endl;
    }
}

// Add a new debt
void addDebt(vector<Debt>& debts) {
    Debt d;
    cout << "Enter name: "; cin >> ws; getline(cin, d.name);
    cout << "Enter amount: "; cin >> d.amount;
    cout << "Enter due date (YYYY-MM-DD): "; cin >> d.dueDate;
    debts.push_back(d);
}

// Remove debt by name
void removeDebt(vector<Debt>& debts) {
    string name;
    cout << "Enter name to remove: "; cin >> ws; getline(cin, name);
    auto it = remove_if(debts.begin(), debts.end(), [&](const Debt& d) {
        return d.name == name;
    });
    if (it != debts.end()) {
        debts.erase(it, debts.end());
        cout << "Debt removed.\n";
    } else {
        cout << "No debt found for that name.\n";
    }
}

int main() {
    vector<Debt> debts;
    const string filename = "debts.txt";

    loadFromFile(debts, filename);

    int choice;
    do {
        cout << "\nDebt Management System\n";
        cout << "1. Add Debt\n2. Remove Debt\n3. Show Debts\n4. Sort Debts\n5. Save & Exit\n";
        cout << "Choose: "; cin >> choice;

        switch (choice) {
            case 1: addDebt(debts); break;
            case 2: removeDebt(debts); break;
            case 3: showDebts(debts); break;
            case 4: sortDebts(debts); break;
            case 5: saveToFile(debts, filename); cout << "Data saved. Exiting...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 5);

    return 0;
}
