//Convert given binary search tree into threaded binary tree. Traverse it in an in order way Analyze time & space complexity of the algorithm. 
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool isThreaded;

    Node(int val) {
        data = val;
        left = right = NULL;
        isThreaded = false;
    }
};

// Insert into BST
Node* insert(Node* root, int key) {
    if (root == NULL)
        return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);

    return root;
}

// Convert BST to right-threaded tree
Node* createThreaded(Node* root, Node*& prev) {
    if (root == NULL)
        return NULL;

    // Recursion for left subtree
    createThreaded(root->left, prev);

    // If right is NULL, thread it to inorder successor
    if (prev != NULL && prev->right == NULL) {
        prev->right = root;
        prev->isThreaded = true;
    }

    prev = root;

    // Recursion only if not threaded
    if (!root->isThreaded)
        createThreaded(root->right, prev);

    return root;
}

// Leftmost node from a given node
Node* leftMost(Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// Inorder traversal without recursion
void inorderThreaded(Node* root) {
    Node* curr = leftMost(root);

    while (curr != NULL) {
        cout << curr->data << " ";

        // If threaded, follow the thread
        if (curr->isThreaded)
            curr = curr->right;
        else
            curr = leftMost(curr->right);
    }
}

int main() {
    Node* root = NULL;

    // Create BST
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    // Convert to threaded
    Node* prev = NULL;
    createThreaded(root, prev);

    // Inorder traversal
    cout << "Inorder Traversal (Threaded Tree): ";
    inorderThreaded(root);

    return 0;
}
