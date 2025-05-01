// A Dictionary stores keywords & its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. 
// Provide facility to display whole data sorted in ascending/Descending order. Also find how many maximum comparisons may require for finding any keyword.
// Use Height balance tree and find the complexity for finding a keyword.

#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string keyword, meaning;
    Node* left;
    Node* right;
    int height;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

int height(Node* root) {
    return root ? root->height : 0;
}

int getBalance(Node* root) {
    return root ? height(root->left) - height(root->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Right Rotate
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

// Left Rotate
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

// Insert with balancing
Node* insert(Node* root, string k, string m) {
    if (!root) return new Node(k, m);

    if (k < root->keyword)
        root->left = insert(root->left, k, m);
    else if (k > root->keyword)
        root->right = insert(root->right, k, m);
    else {
        cout << "Keyword already exists! Updating meaning...\n";
        root->meaning = m;
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balancing
    if (balance > 1 && k < root->left->keyword)
        return rightRotate(root);
    if (balance < -1 && k > root->right->keyword)
        return leftRotate(root);
    if (balance > 1 && k > root->left->keyword) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && k < root->right->keyword) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// In-order traversal (ascending)
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        inOrder(root->right);
    }
}

// Reverse In-order traversal (descending)
void reverseInOrder(Node* root) {
    if (root) {
        reverseInOrder(root->right);
        cout << root->keyword << " : " << root->meaning << endl;
        reverseInOrder(root->left);
    }
}

// Find min value node (for delete)
Node* minValueNode(Node* root) {
    Node* current = root;
    while (current->left)
        current = current->left;
    return current;
}

// Delete a node
Node* deleteNode(Node* root, string k) {
    if (!root)
        return root;

    if (k < root->keyword)
        root->left = deleteNode(root->left, k);
    else if (k > root->keyword)
        root->right = deleteNode(root->right, k);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->keyword = temp->keyword;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->keyword);
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balance after deletion
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search with comparison count
bool search(Node* root, string k, int& comparisons) {
    while (root) {
        comparisons++;
        if (k == root->keyword) {
            cout << "Found: " << root->keyword << " - " << root->meaning << endl;
            return true;
        }
        else if (k < root->keyword)
            root = root->left;
        else
            root = root->right;
    }
    cout << "Keyword not found.\n";
    return false;
}

// Count height of AVL tree
int getHeight(Node* root) {
    return root ? root->height : 0;
}

// Driver menu
int main() {
    Node* root = nullptr;
    int choice;
    string k, m;

    do {
        cout << "\n--- Dictionary Menu ---";
        cout << "\n1. Add/Update Keyword";
        cout << "\n2. Delete Keyword";
        cout << "\n3. Search Keyword";
        cout << "\n4. Display Ascending";
        cout << "\n5. Display Descending";
        cout << "\n6. Max Comparisons Required";
        cout << "\n7. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter keyword: ";
            getline(cin, k);
            cout << "Enter meaning: ";
            getline(cin, m);
            root = insert(root, k, m);
            break;
        case 2:
            cout << "Enter keyword to delete: ";
            getline(cin, k);
            root = deleteNode(root, k);
            break;
        case 3: {
            cout << "Enter keyword to search: ";
            getline(cin, k);
            int comp = 0;
            search(root, k, comp);
            cout << "Comparisons made: " << comp << endl;
            break;
        }
        case 4:
            cout << "\nDictionary (Ascending):\n";
            inOrder(root);
            break;
        case 5:
            cout << "\nDictionary (Descending):\n";
            reverseInOrder(root);
            break;
        case 6:
            cout << "Max comparisons = height of AVL Tree = " << getHeight(root) << endl;
            break;
        case 7:
            cout << "Exiting. Thank You for using this program!\n";
            break;
        default:
            cout << "Invalid choice! Please enter valid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
