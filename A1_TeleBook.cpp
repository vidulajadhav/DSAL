/* Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number. 
Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers */

#include <iostream>
#include <vector>
using namespace std;

const int TABLE_SIZE = 10;

class LinearProbingHash {
    int table[TABLE_SIZE] = {-1};

public:
    LinearProbingHash() { fill(begin(table), end(table), -1); }

    void insert(int key) {
        int idx = key % TABLE_SIZE, start = idx;
        while (table[idx] != -1) {
            idx = (idx + 1) % TABLE_SIZE;
            if (idx == start) { 
                cout << "Hash table is full!\n"; 
                return; }
        }
        table[idx] = key;
    }

    int search(int key, int &comparisons) {
        int idx = key % TABLE_SIZE, start = idx;
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
        cout << "\nHash Table (Linear Probing):\n";
        for (int i = 0; i < TABLE_SIZE; i++)
            cout << "[" << i << "]: " << (table[i] == -1 ? "Empty" : to_string(table[i])) << '\n';
    }
};

// Chaining
class ChainingHash {
    vector<int> table[TABLE_SIZE];

public:
    void insert(int key) { table[key % TABLE_SIZE].push_back(key); }

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
        cout << "\nHash Table (Chaining):\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "]: ";
            for (int val : table[i]) cout << val << " -> ";
            cout << "NULL\n";
        }
    }
};

int getValid(int type = 0) {
    int x;
    while (true) {
        if (type == 0)
            cout << "Enter 8-digit telephone number: ";
        else
            cout << "Enter number of telephone numbers: ";

        cin >> x;
        if (cin.fail() || (type == 0 && (x < 10000000 || x > 99999999)) || (type == 1 && x <= 0)) {
            cout << "Invalid input! Try again.\n";
            cin.clear(); cin.ignore(10000, '\n');
        } else break;
    }
    return x;
}

int main() {
    int choice;
    do {
        cout << "Choose Collision Handling Technique:\n1. Linear Probing\n2. Chaining\nEnter choice (1 or 2): ";
        cin >> choice;
    } while (choice != 1 && choice != 2);

    int n = getValid(1), num, comparisons;

    if (choice == 1) {
        LinearProbingHash lph;

        while (n--) lph.insert(getValid());
        lph.display();
        cout << "\nSearch Telephone Number\n";
        num = getValid();

        int index = lph.search(num, comparisons);
        cout << (index != -1 ? "Found at index " + to_string(index) : "Not found") 
             << " with " << comparisons << " comparisons.\n";
    } else {
        ChainingHash ch;

        while (n--) ch.insert(getValid());
        ch.display();
        cout << "\nSearch Telephone Number\n";

        num = getValid();
        int index = ch.search(num, comparisons);
        cout << (index != -1 ? "Found in chain at index " + to_string(index) : "Not found") << " with " << comparisons << " comparisons.\n";
    }

    return 0;
}
