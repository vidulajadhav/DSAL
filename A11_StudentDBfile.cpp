// Department maintains a student information. The file contains roll number, name, and division & address. Allow user to add, delete information of student. Display information of particular employee. 
// If record of student does not exist an appropriate message is displayed. If it is, then the system displays  the student details. Use sequential file to main the data.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Student {
public:
    int roll;
    string name;
    string division;
    string address;

    void accept() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division: ";
        getline(cin, division);
        cout << "Enter Address: ";
        getline(cin, address);
    }

    void display() const {
        cout << "\nRoll No: " << roll
             << "\nName: " << name
             << "\nDivision: " << division
             << "\nAddress: " << address << "\n";
    }

    string toString() const {
        return to_string(roll) + "|" + name + "|" + division + "|" + address;
    }

    static Student fromString(const string& str) {
        stringstream ss(str);
        string temp;
        Student s;

        getline(ss, temp, '|');
        s.roll = stoi(temp);
        getline(ss, s.name, '|');
        getline(ss, s.division, '|');
        getline(ss, s.address, '|');

        return s;
    }
};

// Adds a student to the file
void addStudent() {
    Student s;
    s.accept();
    ofstream outFile("student.txt", ios::app);
    outFile << s.toString() << "\n";
    outFile.close();
    cout << "Student added successfully!\n";
}

// Displays student by roll number
void displayStudent(int rollNo) {
    ifstream inFile("student.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        Student s = Student::fromString(line);
        if (s.roll == rollNo) {
            s.display();
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found)
        cout << "Student with roll number " << rollNo << " not found.\n";
}

// Deletes a student by roll number
void deleteStudent(int rollNo) {
    ifstream inFile("student.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool deleted = false;

    while (getline(inFile, line)) {
        Student s = Student::fromString(line);
        if (s.roll != rollNo)
            tempFile << s.toString() << "\n";
        else
            deleted = true;
    }

    inFile.close();
    tempFile.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (deleted)
        cout << "Student with roll number " << rollNo << " deleted successfully!\n";
    else
        cout << "Student with roll number " << rollNo << " not found!\n";
}

int main() {
    int choice, roll;

    do {
        cout << "\n--- Student Record Management ---";
        cout << "\n1. Add Student";
        cout << "\n2. Display Student";
        cout << "\n3. Delete Student";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            cout << "Enter roll number to search: ";
            cin >> roll;
            displayStudent(roll);
            break;
        case 3:
            cout << "Enter roll number to delete: ";
            cin >> roll;
            deleteStudent(roll);
            break;
        case 4:
            cout << "Exiting. Thank You for using the program!\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

