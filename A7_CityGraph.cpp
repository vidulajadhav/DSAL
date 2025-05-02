// There are flight paths between cities. If there is a flight between City A and City B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, 
// or the amount of fuel used for the journey. Represent this as a graph. The node can be represented by the  airport name or name of the city. Use adjacency list representation of the graph or use 
// adjacency  matrix representation of the graph. 
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

// ---------------- Adjacency Matrix ----------------
class AdjacencyMatrix {
    int am[10][10];
    char city[10][10];
    int cityCount;

public:
    AdjacencyMatrix() {
        cityCount = 0;
        for (int i = 0; i < 10; i++) {
            strcpy(city[i], "");
            for (int j = 0; j < 10; j++) am[i][j] = 0;
        }
    }

    void createMatrix() {
        char s[10], d[10], ch;
        int si, di, dist;

        do {
            cout << "Enter source city: "; cin >> s;
            cout << "Enter destination city: "; cin >> d;

            si = getCityIndex(s);
            di = getCityIndex(d);

            cout << "Enter distance from " << s << " to " << d << ": ";
            cin >> dist;
            am[si][di] = dist;

            cout << "Do you want to add more? (y/n): ";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');
    }

    void displayMatrix() {
        cout << "\nAdjacency Matrix:\n\t";
        for (int i = 0; i < cityCount; i++) cout << city[i] << "\t";
        cout << "\n";

        for (int i = 0; i < cityCount; i++) {
            cout << city[i] << "\t";
            for (int j = 0; j < cityCount; j++)
                cout << am[i][j] << "\t";
            cout << "\n";
        }
    }

private:
    int getCityIndex(const char* name) {
        for (int i = 0; i < cityCount; i++)
            if (strcmp(city[i], name) == 0)
                return i;
        strcpy(city[cityCount], name);
        return cityCount++;
    }
};

// ---------------- Adjacency List ----------------
class AdjacencyList {
    struct Node {
        int dest;
        int weight;
        Node* next;
    };

    Node* head[10];
    char city[10][10];
    int cityCount;

public:
    AdjacencyList() {
        cityCount = 0;
        for (int i = 0; i < 10; i++) {
            head[i] = nullptr;
            strcpy(city[i], "");
        }
    }

    void createList() {
        char s[10], d[10], ch;
        int si, di, dist;

        do {
            cout << "Enter source city: "; cin >> s;
            cout << "Enter destination city: "; cin >> d;

            si = getCityIndex(s);
            di = getCityIndex(d);

            cout << "Enter distance from " << s << " to " << d << ": ";
            cin >> dist;

            addEdge(si, di, dist);

            cout << "Do you want to add more? (y/n): ";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');
    }

    void displayList() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < cityCount; i++) {
            cout << city[i] << " -> ";
            Node* temp = head[i];
            while (temp) {
                cout << city[temp->dest] << "(" << temp->weight << ") -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }

private:
    int getCityIndex(const char* name) {
        for (int i = 0; i < cityCount; i++)
            if (strcmp(city[i], name) == 0)
                return i;
        strcpy(city[cityCount], name);
        return cityCount++;
    }

    void addEdge(int src, int dest, int wt) {
        Node* newNode = new Node{ dest, wt, head[src] };
        head[src] = newNode;
    }
};

// ---------------- Main Menu ----------------
int main() {
    int mainChoice, subChoice;
    char cont;

    do {
        cout << "\n--- Representation Menu ---\n";
        cout << "1. Adjacency Matrix\n";
        cout << "2. Adjacency List\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                AdjacencyMatrix mat;
                do {
                    cout << "\n--- Adjacency Matrix Menu ---\n";
                    cout << "1. Create Graph\n";
                    cout << "2. Display Graph\n";
                    cout << "3. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1: mat.createMatrix(); break;
                        case 2: mat.displayMatrix(); break;
                        case 3: break;
                        default: cout << "Invalid choice.\n";
                    }
                } while (subChoice != 3);
                break;
            }

            case 2: {
                AdjacencyList list;
                do {
                    cout << "\n--- Adjacency List Menu ---\n";
                    cout << "1. Create Graph\n";
                    cout << "2. Display Graph\n";
                    cout << "3. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1: list.createList(); break;
                        case 2: list.displayList(); break;
                        case 3: break;
                        default: cout << "Invalid choice.\n";
                    }
                } while (subChoice != 3);
                break;
            }

            case 3:
                cout << "Exiting. Thank you for using this program\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }

        cout << "Return to main menu? (y/n): ";
        cin >> cont;

    } while (cont == 'y' || cont == 'Y');

    return 0;
}

