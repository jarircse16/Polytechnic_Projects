#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Bill {
private:
    string customerName;
    string dateOfPayment;
    int userId;
    double totalUnits;
    double totalAmount;

public:
    Bill(string name, string date, int id, double units) {
        customerName = name;
        dateOfPayment = date;
        userId = id;
        totalUnits = units;
        totalAmount = 0.0;
    }

    void calculateAmount(bool isHomeBill) {
        double unitPrice = isHomeBill ? 5.0 : 10.0;
        totalAmount = totalUnits * unitPrice;
    }
    void displayBill() const { // Add const here
        cout << "Customer Name: " << customerName << endl;
        cout << "Date of Payment: " << dateOfPayment << endl;
        cout << "User ID: " << userId << endl;
        cout << "Total Units: " << totalUnits << endl;
        cout << "Total Amount: " << totalAmount << " TK" << endl;
    }

    int getUserId() const {
        return userId;
    }
};

class ElectricalBillManager {
private:
    vector<Bill> bills;

public:
    void inputBill() {
        string name, date;
        int userId;
        double units;
        int billType;

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Date of Payment: ";
        getline(cin, date);

        cout << "Enter User ID: ";
        cin >> userId;
        cin.ignore(); // Clear the input buffer after reading the integer.

        cout << "Enter Total Units: ";
        cin >> units;

        cout << "Enter Bill Type (1 for Home, 2 for Industrial): ";
        cin >> billType;

        bool isHomeBill = (billType == 1);
        Bill bill(name, date, userId, units);
        bill.calculateAmount(isHomeBill);
        bills.push_back(bill);

        cout << "Bill information added successfully!" << endl;
    }

    void displayBills() const { // Add const here
        if (bills.empty()) {
            cout << "No bills found." << endl;
            return;
        }

        cout << "----- Bill Information -----" << endl;
        for (const Bill& bill : bills) {
            bill.displayBill();
            cout << "-----------------------------" << endl;
        }
    }

    void searchBill() {
        int searchUserId;
        cout << "Enter User ID to search: ";
        cin >> searchUserId;

        auto it = find_if(bills.begin(), bills.end(), [searchUserId](const Bill& bill) {
            return bill.getUserId() == searchUserId;
        });

        if (it != bills.end()) {
            cout << "Bill found!" << endl;
            it->displayBill();
        } else {
            cout << "Bill not found for User ID: " << searchUserId << endl;
        }
    }
};

int main() {
    ElectricalBillManager manager;
    int choice;

    do {
        cout << "\n----------- Menu -----------" << endl;
        cout << "1. Input Bill" << endl;
        cout << "2. Display Bills" << endl;
        cout << "3. Search" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer after reading the integer.

        switch (choice) {
            case 1:
                manager.inputBill();
                break;
            case 2:
                manager.displayBills();
                break;
            case 3:
                manager.searchBill();
                break;
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 4);

    return 0;
}
