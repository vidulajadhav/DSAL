//Read the marks obtained by students of second year in an online examination of particular subject. Find out maximum and minimum marks obtained in that subject. Use heap data structure. 
// Analyze the algorithm

#include <iostream>
#include <vector>
#include <queue> // For heap (priority_queue)
#include <limits>
using namespace std;

void inputMarks(vector<int>& marks) {
	
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    while (n <= 0) {
        cout << "Number of students must be greater than 0. Enter again: ";
        cin >> n;
    }

    cout << "Enter marks of " << n << " students:\n";
    for (int i = 0; i < n; ++i) {
        int mark;
        cout << "Student " << i + 1 << ": ";
        cin >> mark;
        while (mark < 0 || mark > 100) {
            cout << "Invalid mark (0-100). Re-enter: ";
            cin >> mark;
        }
        marks.push_back(mark);
    }
}

void findMaxMinUsingHeap(const vector<int>& marks) {
    // Max Heap for maximum
    priority_queue<int> maxHeap;
    // Min Heap for minimum
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int mark : marks) {
        maxHeap.push(mark);
        minHeap.push(mark);
    }

    cout << "\nMaximum Marks: " << maxHeap.top();
    cout << "\nMinimum Marks: " << minHeap.top() << "\n";
}

int main() {
    vector<int> marks;

    inputMarks(marks);

    if (marks.empty()) {
        cout << "No marks to evaluate.\n";
        return 0;
    }

    findMaxMinUsingHeap(marks);

    return 0;
}
