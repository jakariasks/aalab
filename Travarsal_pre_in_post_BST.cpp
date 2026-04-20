#include <bits/stdc++.h>
using namespace std;

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

// Insert in BST
Node* insertBST(Node* root,int val)
{
    if(root== NULL)
        return new Node(val);

    if(val< root->data)
        root->left =insertBST(root->left, val);
    else if(val >root->data)
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

// Inorder traversal
void inorder(Node* root)
{
    if(root== NULL)
        return;

    inorder(root->left);
    cout<<root->data<< " ";
    inorder(root->right);
}

// Preorder traversal
void preorder(Node* root)
{
    if(root==NULL)
        return;

    cout<<root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder traversal
void postorder(Node* root)
{
    if(root== NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    cout<<root->data<< " ";
}

int main()
{
    vector<int>arr= {7,9,8,3, 2, 1, 5, 6, 4};

    Node* root= buildBST(arr);

    cout<<"\nInorder Traversal BST: ";
    inorder(root);

    cout<<"\nPreorder Traversal BST: ";
    preorder(root);

    cout<<"\nPostorder Traversal BST: ";
    postorder(root);

    cout<<endl;
    return 0;
}

