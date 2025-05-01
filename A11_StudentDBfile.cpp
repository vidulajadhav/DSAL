// Department maintains a student information. The file contains roll number, name, and division & address. Allow user to add, delete information of student. Display information of particular employee. 
// If record of student does not exist an appropriate message is displayed. If it is, then the system displays  the student details. Use sequential file to main the data.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int roll;
    string name;
    char division;
    string address;

    void accept() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division (A/B/C): ";
        cin >> division;
        cin.ignore();
        cout << "Enter Address: ";
        getline(cin, address);
    }

    void display() {
        cout << "\nRoll No: " << roll;
        cout << "\nName: " << name;
        cout << "\nDivision: " << division;
        cout << "\nAddress: " << address << "\n";
    }
};

// Adds a student to the file
void addStudent() {
    Student s;
    s.accept();
    ofstream outFile("student.txt", ios::app);
    outFile << s.roll << "|" << s.name << "|" << s.division << "|" << s.address << "\n";
    outFile.close();
    cout << "Student added successfully!\n";
}

// Displays student by roll number
void displayStudent(int rollNo) {
    ifstream inFile("student.txt");
    Student s;
    bool found = false;
    string line;

    while (getline(inFile, line)) {
        int delim1 = line.find("|");
        int delim2 = line.find("|", delim1 + 1);
        int delim3 = line.find("|", delim2 + 1);

        s.roll = stoi(line.substr(0, delim1));
        s.name = line.substr(delim1 + 1, delim2 - delim1 - 1);
        s.division = line[delim2 + 1];
        s.address = line.substr(delim3 + 1);

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

    Student s;
    string line;
    bool deleted = false;

    while (getline(inFile, line)) {
        int delim1 = line.find("|");
        int delim2 = line.find("|", delim1 + 1);
        int delim3 = line.find("|", delim2 + 1);

        s.roll = stoi(line.substr(0, delim1));

        if (s.roll != rollNo)
            tempFile << line << "\n";
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
