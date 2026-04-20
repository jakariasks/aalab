#include <bits/stdc++.h>

using namespace std;

// Node
struct Node
{
    int data;
    Node* left;
    Node* right;
    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

Node* insertBST(Node* root,int val)
{
    if (root== NULL)
        return new Node(val);
    if (val <root->data)
        root->left= insertBST(root->left, val);
    else
        root->right= insertBST(root->right, val);

    return root;
}

Node* buildBST(vector<int>& arr)
{
    Node* root = NULL;
    for(int val : arr)
    {
        root=insertBST(root, val);
    }
    return root;
}

void inorder(Node* root)
{
    if (root==NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

bool searchBST (Node* root,int key)
    {
        if(root == NULL)
            return false;
        if(root->data == key)
            return true;
        if (root->data < key )
            return searchBST (root->right,key);
        else
            return searchBST (root->left,key);
    }

int main()
{

    Node* root;
    vector<int> arr = {7,9,8,3, 2, 1, 5, 6, 4};
    root= buildBST(arr);
    cout << "Inorder Traversal In BST: ";
    inorder(root);
    cout << endl;


    //BST search
    int key;
    cout << "\nEnter a value to search in BST: ";
    cin >> key;

    if (searchBST(root, key))
        cout <<key << " is found\n";
    else
        cout <<key<< " is not found\n";


    return 0;
}
