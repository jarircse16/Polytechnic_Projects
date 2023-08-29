#include <iostream>
#include <string>

using namespace std;

class Student {
private:
    string name;
    int id;
    int marks[4];

public:
    void setter() {
        cout << "Enter student name: ";
        getline(cin, name); // Read the full name with spaces

        cout << "Enter student ID: ";
        cin >> id;

        cout << "Enter marks for four subjects:\n";
        for (int i = 0; i < 4; ++i) {
            cout << "Subject " << i + 1 << ": ";
            cin >> marks[i];
        }
    }

    int totalMark() {
        int total = 0;
        for (int i = 0; i < 4; ++i) {
            total += marks[i];
        }
        return total;
    }

    void getter() {
        cout<< endl;
        cout << "Student Name: " << name << endl;
        cout << "Student ID: " << id << endl;
        cout << "Marks in four subjects: ";
        for (int i = 0; i < 4; ++i) {
            cout << marks[i] << " ";
        }
        cout << endl;
        cout << "Total Marks: " << totalMark() << endl;
    }
};

int main() {
    Student student;
    student.setter();
    student.getter();
    return 0;
}
