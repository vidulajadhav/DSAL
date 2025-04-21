/*  Group A Practical 1

Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number. 
Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers */

#include <iostream>
#include <vector>
using namespace std;

const int TABLE_SIZE = 10;

// Linear Probing 
class LinearProbingHash {
    int table[TABLE_SIZE];

public:
    LinearProbingHash() {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = -1;
    }

    void insert(int key) {
        int idx = key % TABLE_SIZE;
        int start = idx;
        while (table[idx] != -1) {
            idx = (idx + 1) % TABLE_SIZE;
            if (idx == start) {
                cout << "Hash table is full!" << endl;
                return;
            }
        }
        table[idx] = key;
    }

    int search(int key, int &comparisons) {
        int idx = key % TABLE_SIZE;
        int start = idx;
        comparisons = 1;
        while (table[idx] != key) {
            if (table[idx] == -1) return -1;
            idx = (idx + 1) % TABLE_SIZE;
            comparisons++;
            if (idx == start) return -1;
        }
        return idx;
    }

    void display() {
        cout << "\nHash Table (Linear Probing):" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "]: ";
            if (table[i] == -1) cout << "Empty";
            else cout << table[i];
            cout << endl;
        }
    }
};

//Chaining
class ChainingHash {
    vector<int> table[TABLE_SIZE];

public:
    void insert(int key) {
        int idx = key % TABLE_SIZE;
        table[idx].push_back(key);
    }

    int search(int key, int &comparisons) {
        int idx = key % TABLE_SIZE;
        comparisons = 0;
        for (int val : table[idx]) {
            comparisons++;
            if (val == key) return idx;
        }
        return -1;
    }

    void display() {
        cout << "\nHash Table (Chaining):" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "]: ";
            for (int val : table[i]) {
                cout << val << " -> ";
            }
            cout << "NULL" << endl;
        }
    }
};

//Input Validation 
int getValidChoice() {
    int choice;
    while (true) {
        cout << "Choose Collision Handling Technique:" << endl;
        cout << "1. Linear Probing" << endl;
        cout << "2. Chaining" << endl;
        cout << "Enter choice (1 or 2): ";
        cin >> choice;

        if (cin.fail() || (choice != 1 && choice != 2)) {
            cout << "Invalid input! Please enter a valid choice (1 or 2).\n" << endl;
        } else {
            break;
        }
    }
    return choice;
}

int getValidPhoneNumber() {
    int num;
    while (true) {
        cout << "Enter 8-digit telephone number: ";
        cin >> num;

        if (cin.fail() || num < 10000000 || num > 99999999) {
            cout << " Invalid number! Please enter a valid 8-digit number.\n";
        } else {
            break;
        }
    }
    return num;
}

// Main Function
int main() {
    int choice = getValidChoice();
    int n, num, comparisons;

    cout << "\nEnter number of telephone numbers to insert: ";
    while (!(cin >> n) || n <= 0) {
        cout << " Invalid input! Please enter a positive integer: ";
    }

    if (choice == 1) {
        LinearProbingHash lph;
        for (int i = 0; i < n; i++) {
            num = getValidPhoneNumber();
            lph.insert(num);
        }

        lph.display();

        cout << "\nSearch Telephone Number\n";
        num = getValidPhoneNumber();
        int index = lph.search(num, comparisons);
        if (index != -1)
            cout << "Number found at index " << index << " with " << comparisons << " comparisons." << endl;
        else
            cout << "Number not found. Comparisons made: " << comparisons << endl;

    } else if (choice == 2) {
        ChainingHash ch;
        for (int i = 0; i < n; i++) {
            num = getValidPhoneNumber();
            ch.insert(num);
        }

        ch.display();

        cout << "\nSearch Telephone Number\n";
        num = getValidPhoneNumber();
        int index = ch.search(num, comparisons);
        if (index != -1)
            cout << "Number found in chain at index " << index << " with " << comparisons << " comparisons." << endl;
        else
            cout << "Number not found. Comparisons made: " << comparisons << endl;
    }

    return 0;
}
