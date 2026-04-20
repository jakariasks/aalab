#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};


Node* createNode(int val) {
    return new Node{val, NULL, NULL};
}


Node* insert(Node* root, int val)
{
    if(!root)
        return createNode(val);

    if(val<root->data)
        root->left =insert(root->left,val);
    else
        root->right =insert(root->right, val);

    return root;
}

void printTree(Node* root)
{
    if(!root) return;

    cout<< "        " << root->data <<endl;

    if(root->left||root->right)
        {
        cout<< "       /  \\" <<endl;
    }

    if(root->left && root->right)
        {
        cout<< "     " << root->left->data<< "    " << root->right->data<<endl;

        cout<< "    / \\    / \\" <<endl;

        cout<< "  " << root->left->left->data
             << "  " << root->left->right->data
             << "  " << root->right->left->data
             << "  " << root->right->right->data<<endl;
    }
}

int main()
{

    Node* root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for(int v : values)
        root = insert(root, v);

    printTree(root);
    return 0;
}

