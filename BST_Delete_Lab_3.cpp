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

Node* getInorderSuccesor(Node* root)
{
    while(root !=NULL && root->left !=NULL)
    {
        root = root->left;
    }
    return root;
}
Node* deleteBST(Node* root, int key)
{
    if(root == NULL)
        return NULL;

    if(key <root->data)
        root->left = deleteBST(root->left, key);
    else if(key > root->data)
        root->right = deleteBST(root->right, key);
    else
    {
        if (root->left ==NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if(root ->right == NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        else
        {
            Node* IS = getInorderSuccesor(root->right);
            root-> data = IS->data;
            root->right = deleteBST(root->right, IS->data);
        }
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



int main()
{

    Node* root;
    vector<int> arr = {7,9,8,3, 2, 1, 5, 6, 4};
    root= buildBST(arr);

    cout<<"Befor Delete"<<endl;
    cout << "Inorder Traversal In BST: ";
    inorder(root);
    cout << endl<<endl;

    int key = 8;
    deleteBST(root,key);

    cout<<"After Delete "<<key <<endl;
    cout << "Inorder Traversal In BST: ";
    inorder(root);
    cout << endl;


    return 0;
}

