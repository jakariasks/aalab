
#include <bits/stdc++.h>
using namespace std;


struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Insert into NORMAL Binary Tree (level order)
Node* insertNode(Node* root, int val) {
    if (root == NULL)
        return new Node(val);

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->left == NULL) {
            temp->left = new Node(val);
            break;
        } else {
            q.push(temp->left);
        }

        if (temp->right == NULL) {
            temp->right = new Node(val);
            break;
        } else {
            q.push(temp->right);
        }
    }
    return root;
}

// Vertical tree display (level order with spacing)
void printVerticalTree(Node* root)
{
    if (root == NULL) {
        cout << "Tree is empty\n";
        return;
    }

    queue<Node*> q;
    q.push(root);

    int level = 0;
    const int baseSpace = 60;

    while (!q.empty())
    {
        int size = q.size();
        int spacing = baseSpace / (1 << level);
        if (spacing < 2) spacing = 2;

        cout << setw(spacing / 2) << "";

        for (int i = 0; i < size; i++)
        {
            Node* p = q.front();
            q.pop();

            cout << p->data << setw(spacing);

            if (p->left)  q.push(p->left);
            if (p->right) q.push(p->right);
        }

        cout << "\n\n";
        level++;

        // safety limit for lab usage
        if (level > 6) break;
    }
}

int main() {
    Node* root = NULL;
    int n, val;

    cout << "Enter number of nodes: ";
    cin >> n;

    if (n <= 0) {
        cout << "Tree is empty\n";
        return 0;
    }

    cout << "Enter node values one by one:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        root = insertNode(root, val);
    }

    cout << "\nBinary Tree Structure:\n\n";
    printVerticalTree(root);

    return 0;
}
