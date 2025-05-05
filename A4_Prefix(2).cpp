// 4. Construct an expression tree from the given prefix expression:  
// +--a*bc/def and traverse it using post order traversal (non -recursive) and then delete the entire tree

#include <iostream>
#include <stack>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char val) {
        data = val;
        left = right = NULL;
    }
};

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Build expression tree from prefix
Node* buildExpressionTree(string prefix) {
    stack<Node*> stk;

    // Traverse prefix expression from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];

        Node* newNode = new Node(ch);

        if (isOperator(ch)) {
            newNode->left = stk.top(); stk.pop();
            newNode->right = stk.top(); stk.pop();
        }

        stk.push(newNode);
    }

    return stk.top();
}

// Non-recursive postorder traversal using two stacks
void postOrderNonRecursive(Node* root) {
    if (root == NULL) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* temp = s1.top(); s1.pop();
        s2.push(temp);

        if (temp->left) s1.push(temp->left);
        if (temp->right) s1.push(temp->right);
    }

    cout << "\nPostorder traversal: ";
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
    cout << endl;
    cout << endl;
}

// Postorder delete tree (recursive is fine here)
void deleteTree(Node* root) {
    if (root == NULL) return;

    deleteTree(root->left);
    deleteTree(root->right);

    cout << "Deleting node: " << root->data << endl;
    delete root;
    
}

int main() {
    string prefix ;
    cout<<"Enter the prefix expression: ";
    cin >> prefix;
    cout << "\nBuilding Expression Tree for prefix: " << prefix ;

    Node* root = buildExpressionTree(prefix);
    postOrderNonRecursive(root);
    deleteTree(root);
    cout << "\nTree deleted successfully.\n";

    return 0;
}
