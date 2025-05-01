// Construct an expression tree from the given prefix expression:  
// +--a*bc/def and traverse it using post order traversal (non -recursive) and then delete the entire tree. 

#include <iostream>
#include <stack>
using namespace std;

// Tree Node
class Node {
public:
    char data;
    Node *left, *right;

    Node(char val) {
        data = val;
        left = right = nullptr;
    }
};

// Expression Tree Class
class ExpressionTree {
private:
    Node* root;

    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }

public:
    ExpressionTree() {
        root = nullptr;
    }

    // Construct tree from prefix expression
    void buildFromPrefix(const string& prefix) {
        stack<Node*> st;

        // Traverse right to left
        for (int i = prefix.size() - 1; i >= 0; --i) {
            char ch = prefix[i];
            Node* node = new Node(ch);

            if (isOperator(ch)) {
                // Pop two nodes as children
                if (st.size() < 2) {
                    cerr << "Invalid prefix expression\n";
                    return;
                }
                node->left = st.top(); st.pop();
                node->right = st.top(); st.pop();
            }
            st.push(node);
        }

        if (st.size() != 1) {
            cerr << "Invalid prefix expression\n";
            return;
        }

        root = st.top();
    }

    // Non-recursive postorder traversal using two stacks
    void postOrderNonRecursive() {
        if (!root) {
            cout << "Tree is empty.\n";
            return;
        }

        stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node* curr = s1.top(); s1.pop();
            s2.push(curr);

            if (curr->left) s1.push(curr->left);
            if (curr->right) s1.push(curr->right);
        }

        cout << "Postorder Traversal (non-recursive): ";
        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
        cout << endl;
    }

    // Delete the tree using postorder traversal
    void deleteTree() {
        if (!root) return;

        stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node* curr = s1.top(); s1.pop();
            s2.push(curr);

            if (curr->left) s1.push(curr->left);
            if (curr->right) s1.push(curr->right);
        }

        while (!s2.empty()) {
            Node* temp = s2.top(); s2.pop();
            delete temp;
        }

        root = nullptr;
        cout << "Tree deleted successfully.\n";
    }
};

int main() {
    ExpressionTree tree;
    string prefix = "+--a*bc/def";

    cout << "Building Expression Tree for prefix: " << prefix << endl;
    tree.buildFromPrefix(prefix);

    tree.postOrderNonRecursive();

    tree.deleteTree();

    return 0;
}
