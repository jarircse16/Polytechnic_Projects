#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <mysql/jdbc.h>

using namespace std;
using namespace sql;

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

    void displayBill() const {
        cout << "Customer Name: " << customerName << endl;
        cout << "Date of Payment: " << dateOfPayment << endl;
        cout << "User ID: " << userId << endl;
        cout << "Total Units: " << totalUnits << endl;
        cout << "Total Amount: " << totalAmount << " TK" << endl;
    }

    int getUserId() const {
        return userId;
    }

    double getTotalAmount() const {
        return totalAmount;
    }

    string getCustomerName() const {
        return customerName;
    }

    string getDateOfPayment() const {
        return dateOfPayment;
    }

    double getTotalUnits() const {
        return totalUnits;
    }

    void setTotalAmount(double amount) {
        totalAmount = amount;
    }
};

class ElectricalBillManager {
private:
    vector<Bill> bills;

public:
    void inputBill() {
        string name, date;
        int id;
        double units;
        char billType;

        cout << "Enter customer name: ";
        getline(cin, name);

        cout << "Enter date of payment: ";
        getline(cin, date);

        cout << "Enter user ID: ";
        cin >> id;

        cout << "Enter total units: ";
        cin >> units;

        cout << "Enter bill type (H for Home / I for Industrial): ";
        cin >> billType;
        cin.ignore(); // Clear the input buffer after reading the character.

        bool isHomeBill = (billType == 'H' || billType == 'h');

        Bill bill(name, date, id, units);
        bill.calculateAmount(isHomeBill);
        bills.push_back(bill);

        cout << "Bill added successfully!" << endl;
    }

    void displayBills() const {
        if (bills.empty()) {
            cout << "No bills found." << endl;
            return;
        }

        cout << "----- Bill Information -----" << endl;
        for (const Bill &bill : bills) {
            bill.displayBill();
            cout << "-----------------------------" << endl;
        }
    }

    void searchBill() {
        int searchId;
        cout << "Enter the user ID to search for: ";
        cin >> searchId;

        bool found = false;
        for (const Bill &bill : bills) {
            if (bill.getUserId() == searchId) {
                bill.displayBill();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Bill not found for the given user ID." << endl;
        }
    }

    vector<Bill> getBills() const {
        return bills;
    }
};


void saveBillsToDatabase(const vector<Bill>& bills) {
    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::PreparedStatement *pstmt;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "your_fake_username", "your_fake_password");
        con->setSchema("your_fake_database_name");

        pstmt = con->prepareStatement("INSERT INTO bills (userId, totalAmount, customerName, dateOfPayment, totalUnits) VALUES (?, ?, ?, ?, ?)");

        for (const Bill &bill : bills) {
            pstmt->setInt(1, bill.getUserId());
            pstmt->setDouble(2, bill.getTotalAmount());
            pstmt->setString(3, bill.getCustomerName());
            pstmt->setString(4, bill.getDateOfPayment());
            pstmt->setDouble(5, bill.getTotalUnits());

            pstmt->executeUpdate();
        }

        delete pstmt;
        delete con;
        cout << "Bills saved to the database successfully!" << endl;
    } catch (sql::SQLException &e) {
        cout << "Error: " << e.what() << endl;
    }
}

vector<Bill> loadBillsFromDatabase() {
    vector<Bill> loadedBills;

    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "your_fake_username", "your_fake_password");
        con->setSchema("your_fake_database_name");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM bills");

        while (res->next()) {
            int userId = res->getInt("userId");
            double totalAmount = res->getDouble("totalAmount");
            string customerName = res->getString("customerName");
            string dateOfPayment = res->getString("dateOfPayment");
            double totalUnits = res->getDouble("totalUnits");

            Bill bill(customerName, dateOfPayment, userId, totalUnits);
            bill.setTotalAmount(totalAmount);
            loadedBills.push_back(bill);
        }

        delete res;
        delete stmt;
        delete con;
        cout << "Bills loaded from the database successfully!" << endl;
    } catch (sql::SQLException &e) {
        cout << "Error: " << e.what() << endl;
    }

    return loadedBills;
}

int main() {
    vector<Bill> bills = loadBillsFromDatabase();
    ElectricalBillManager manager(bills);

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

    saveBillsToDatabase(manager.getBills());

    return 0;
}
