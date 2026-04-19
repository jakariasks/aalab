/*
================================================================================
     ADVANCED ALGORITHMS - COMPLETE LAB SOLUTIONS (ALL UNITS 1-8)
================================================================================
 Topics Covered:
   UNIT 1  : Binary Tree & BST (Lab 1-2)
   UNIT 2  : Tree Traversals - Stack & Recursive (Lab 3-8)
   UNIT 3  : BST Deletion (Lab 9-11)
   UNIT 4  : Heap Sort, Max/Min Heap, Huffman Coding (Lab 12-13, 25-26)
   UNIT 5  : AVL Tree, Red-Black Tree (Lab 14-15)
   UNIT 6  : Graph Operations, BFS, DFS (Lab 16-18)
   UNIT 7  : Warshall, Floyd-Warshall, Shortest Path (Lab 19-21)
   UNIT 8  : TSP, Fractional Knapsack, 0/1 Knapsack (Lab 22-24)
================================================================================
 Compile: g++ -std=c++17 -o advanced_algorithms advanced_algorithms.cpp
 Run    : ./advanced_algorithms
================================================================================
*/

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <climits>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <set>

using namespace std;

// ============================================================
//  SEPARATOR HELPER
// ============================================================
void printSeparator(const string& title) {
    cout << "\n";
    cout << "================================================================\n";
    cout << "  " << title << "\n";
    cout << "================================================================\n";
}

void printSubSeparator(const string& title) {
    cout << "\n--- " << title << " ---\n";
}


// ============================================================
// ██╗   ██╗███╗   ██╗██╗████████╗   ██╗
// ██║   ██║████╗  ██║██║╚══██╔══╝  ███║
// ██║   ██║██╔██╗ ██║██║   ██║     ╚██║
// ██║   ██║██║╚██╗██║██║   ██║      ██║
// ╚██████╔╝██║ ╚████║██║   ██║      ██║
//  ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝      ╚═╝
// UNIT 1: BINARY TREE & BINARY SEARCH TREE
// ============================================================

// ─── Node structure used by Binary Tree AND BST ───
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ============================================================
// LAB 1: Binary Tree Construction
// ============================================================

/*
 * Binary Tree: A tree where each node has AT MOST 2 children.
 * No ordering constraint (unlike BST).
 *
 * Approach here: level-order insertion so the tree stays
 * complete (left-to-right, level by level).
 */

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    // ── Insert a new node using level-order (BFS) to keep tree complete ──
    void insert(int val) {
        TreeNode* newNode = new TreeNode(val);
        if (!root) {            // Tree is empty – new node becomes root
            root = newNode;
            return;
        }
        // Use a queue to find the first node that has a free child slot
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            if (!curr->left) {          // Left slot free – insert here
                curr->left = newNode;
                return;
            } else {
                q.push(curr->left);     // Left child exists – explore it later
            }
            if (!curr->right) {         // Right slot free – insert here
                curr->right = newNode;
                return;
            } else {
                q.push(curr->right);
            }
        }
    }

    // ── Display tree visually (rotated 90°, right subtree on top) ──
    // Spaces help show depth; deeper nodes are indented more.
    void displayTree(TreeNode* node, int space = 0, int indent = 4) {
        if (!node) return;
        space += indent;
        displayTree(node->right, space, indent);   // Print right subtree first
        cout << "\n" << string(space - indent, ' ') << node->data << "\n";
        displayTree(node->left, space, indent);    // Then left subtree
    }

    void display() {
        cout << "Tree structure (right→ top, left→ bottom):\n";
        displayTree(root);
    }
};

// ============================================================
// LAB 2: Binary Search Tree (BST) – FIND & INSERT
// ============================================================

/*
 * BST Property:
 *   • All values in left  subtree < node value
 *   • All values in right subtree > node value
 *
 * FIND  Algorithm: Compare target with current node;
 *                  go left if smaller, right if larger.
 * INSERT Algorithm: Follow FIND path until nullptr slot found.
 */

class BST {
public:
    TreeNode* root;
    BST() : root(nullptr) {}

    // ── FIND Algorithm ──────────────────────────────────────
    // Returns pointer to the node if found, else nullptr.
    TreeNode* find(TreeNode* node, int key) {
        if (!node) {
            cout << "  [FIND] " << key << " NOT found in BST.\n";
            return nullptr;
        }
        if (key == node->data) {
            cout << "  [FIND] " << key << " FOUND in BST.\n";
            return node;
        }
        if (key < node->data)
            return find(node->left, key);   // Search left subtree
        else
            return find(node->right, key);  // Search right subtree
    }

    // ── INSERT Algorithm ─────────────────────────────────────
    // Recursively finds correct position maintaining BST property.
    TreeNode* insert(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);   // Empty slot found – insert
        if (key < node->data)
            node->left  = insert(node->left,  key);  // Go left
        else if (key > node->data)
            node->right = insert(node->right, key);  // Go right
        // If key == node->data: duplicate, ignore (BSTs typically skip dups)
        return node;
    }

    void insert(int key) {
        root = insert(root, key);
        cout << "  [INSERT] " << key << " inserted into BST.\n";
    }

    void find(int key) { find(root, key); }

    // Inorder traversal to verify BST (should print sorted order)
    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Display tree visually (same as BinaryTree::displayTree)
    void displayTree(TreeNode* node, int space = 0, int indent = 4) {
        if (!node) return;
        space += indent;
        displayTree(node->right, space, indent);
        cout << "\n" << string(space - indent, ' ') << node->data << "\n";
        displayTree(node->left, space, indent);
    }

    void display() {
        cout << "BST structure:\n";
        displayTree(root);
        cout << "\nInorder (sorted): ";
        inorder(root);
        cout << "\n";
    }
};


// ============================================================
// ██╗   ██╗███╗   ██╗██╗████████╗   ██████╗
// ██║   ██║████╗  ██║██║╚══██╔══╝  ╚════██╗
// ██║   ██║██╔██╗ ██║██║   ██║      █████╔╝
// ██║   ██║██║╚██╗██║██║   ██║     ██╔═══╝
// ╚██████╔╝██║ ╚████║██║   ██║     ███████╗
//  ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝     ╚══════╝
// UNIT 2: TREE TRAVERSAL TECHNIQUES
// ============================================================

/*
 * Three standard DFS traversals:
 *   Preorder  : Root → Left → Right
 *   Inorder   : Left → Root → Right  (gives sorted order for BST)
 *   Postorder : Left → Right → Root
 *
 * Implemented BOTH iteratively (using explicit Stack) AND recursively.
 */

// ============================================================
// PART A – TRAVERSAL USING STACK (NON-RECURSIVE)
// ============================================================

// ── LAB 3: Preorder Traversal using Stack ──────────────────
// Algorithm:
//  1. Push root onto stack.
//  2. While stack not empty:
//       a. Pop node, VISIT it.
//       b. Push right child (if exists).
//       c. Push left  child (if exists).
//     (Right pushed before left so left is processed first)
void preorderStack(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* curr = st.top(); st.pop();
        cout << curr->data << " ";          // Visit
        if (curr->right) st.push(curr->right);
        if (curr->left)  st.push(curr->left);
    }
}

// ── LAB 4: Inorder Traversal using Stack ───────────────────
// Algorithm:
//  1. Start at root with empty stack.
//  2. Push nodes going as far LEFT as possible.
//  3. Pop, VISIT, then move to RIGHT child.
//  4. Repeat until stack empty AND current == nullptr.
void inorderStack(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;
    while (curr || !st.empty()) {
        while (curr) {                      // Go left as far as possible
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        cout << curr->data << " ";          // Visit
        curr = curr->right;                 // Move to right subtree
    }
}

// ── LAB 5: Postorder Traversal using Stack ─────────────────
// Algorithm (Two-Stack method):
//  1. Push root to stack1.
//  2. While stack1 not empty:
//       a. Pop to stack2.
//       b. Push left  child to stack1.
//       c. Push right child to stack1.
//  3. Pop and VISIT all from stack2 (gives postorder).
void postorderStack(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        TreeNode* curr = st1.top(); st1.pop();
        st2.push(curr);                     // Defer visiting to later
        if (curr->left)  st1.push(curr->left);
        if (curr->right) st1.push(curr->right);
    }
    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// ============================================================
// PART B – TRAVERSAL USING RECURSION
// ============================================================

// ── LAB 6: Preorder Traversal (Recursive) ──────────────────
void preorderRecursive(TreeNode* node) {
    if (!node) return;
    cout << node->data << " ";              // Visit ROOT first
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}

// ── LAB 7: Inorder Traversal (Recursive) ───────────────────
void inorderRecursive(TreeNode* node) {
    if (!node) return;
    inorderRecursive(node->left);
    cout << node->data << " ";              // Visit ROOT in middle
    inorderRecursive(node->right);
}

// ── LAB 8: Postorder Traversal (Recursive) ─────────────────
void postorderRecursive(TreeNode* node) {
    if (!node) return;
    postorderRecursive(node->left);
    postorderRecursive(node->right);
    cout << node->data << " ";              // Visit ROOT last
}


// ============================================================
// ██╗   ██╗███╗   ██╗██╗████████╗   ██████╗
// ██║   ██║████╗  ██║██║╚══██╔══╝   ╚════██╗
// ██║   ██║██╔██╗ ██║██║   ██║          ██╔╝
// ██║   ██║██║╚██╗██║██║   ██║         ██╔╝
// ╚██████╔╝██║ ╚████║██║   ██║        ██║
//  ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝        ╚═╝
// UNIT 3: DELETION IN BST
// ============================================================

/*
 * BST Deletion – three cases:
 *  Case 1 (Lab 9) : Node has NO children   → simply remove it.
 *  Case 2 (Lab 10): Node has ONE child      → link parent directly to that child.
 *  Case 3 (Lab 11): Node has TWO children  → replace with inorder successor
 *                   (smallest in right subtree), then delete that successor.
 */

// ── Helper: find minimum node in a subtree ─────────────────
TreeNode* findMin(TreeNode* node) {
    while (node->left) node = node->left;
    return node;
}

// ── LAB 9 / 10 / 11: BST Delete (handles all three cases) ──
TreeNode* deleteBST(TreeNode* node, int key) {
    if (!node) {
        cout << "  [DELETE] " << key << " not found.\n";
        return nullptr;
    }
    if (key < node->data) {
        node->left  = deleteBST(node->left,  key);   // Search left
    } else if (key > node->data) {
        node->right = deleteBST(node->right, key);   // Search right
    } else {
        // Found the node to delete
        cout << "  [DELETE] Deleting node " << key << " → ";

        // Case 1: No children (leaf node)
        if (!node->left && !node->right) {
            cout << "Leaf node removed.\n";
            delete node;
            return nullptr;
        }
        // Case 2a: Only right child
        else if (!node->left) {
            cout << "Node with only right child removed.\n";
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        // Case 2b: Only left child
        else if (!node->right) {
            cout << "Node with only left child removed.\n";
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        // Case 3: Two children – find inorder successor
        else {
            TreeNode* successor = findMin(node->right);
            cout << "Two children; inorder successor = " << successor->data << "\n";
            node->data  = successor->data;             // Copy successor value
            node->right = deleteBST(node->right, successor->data); // Delete successor
        }
    }
    return node;
}


// ============================================================
// ██╗   ██╗███╗   ██╗██╗████████╗  ██╗  ██╗
// ██║   ██║████╗  ██║██║╚══██╔══╝  ██║  ██║
// ██║   ██║██╔██╗ ██║██║   ██║     ███████║
// ██║   ██║██║╚██╗██║██║   ██║     ╚════██║
// ╚██████╔╝██║ ╚████║██║   ██║          ██║
//  ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝          ╚═╝
// UNIT 4: HEAP & GREEDY / CODING ALGORITHMS
// ============================================================

// ============================================================
// LAB 12: HEAP SORT
// ============================================================

/*
 * Heap Sort Concept:
 *   1. Build a MAX-HEAP from the array  (heapify all internal nodes bottom-up).
 *   2. Repeatedly swap root (max element) with last element,
 *      reduce heap size by 1, and heapify root to restore heap property.
 * Time Complexity: O(n log n)  |  Space: O(1) in-place.
 *
 * MAX-HEAP Property: parent >= children
 */

// ── Heapify: maintain max-heap property at index i (heap size = n) ──
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;         // Assume current node is largest
    int left    = 2*i + 1;  // Left child index
    int right   = 2*i + 2;  // Right child index

    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {                     // Root is not the largest
        swap(arr[i], arr[largest]);         // Swap with largest child
        heapify(arr, n, largest);           // Recursively heapify affected subtree
    }
}

// ── Heap Sort main function ──────────────────────────────────
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Phase 1: Build max-heap (start from last internal node, go up to root)
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Phase 2: Extract elements one by one from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);   // Move current root (max) to end
        heapify(arr, i, 0);     // Heapify the reduced heap
    }
}

// ============================================================
// LAB 25: Create MAX HEAP
// ============================================================
/*
 * Max-Heap: parent.value >= children.values
 * Stored as a 1D array; for node at index i:
 *   left child  = 2i+1,  right child = 2i+2,  parent = (i-1)/2
 */
class MaxHeap {
    vector<int> heap;

    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent] < heap[i]) {
                swap(heap[parent], heap[i]);
                i = parent;
            } else break;
        }
    }

    void siftDown(int i) {
        int n = heap.size();
        while (true) {
            int largest = i, l = 2*i+1, r = 2*i+2;
            if (l < n && heap[l] > heap[largest]) largest = l;
            if (r < n && heap[r] > heap[largest]) largest = r;
            if (largest == i) break;
            swap(heap[i], heap[largest]);
            i = largest;
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        siftUp(heap.size() - 1);   // Bubble up to correct position
    }

    int extractMax() {
        if (heap.empty()) { cout << "Heap empty!\n"; return -1; }
        int maxVal = heap[0];
        heap[0] = heap.back();      // Move last element to root
        heap.pop_back();
        siftDown(0);                // Push down to correct position
        return maxVal;
    }

    void display() {
        cout << "Max-Heap array: ";
        for (int v : heap) cout << v << " ";
        cout << "\n";
    }
};

// ============================================================
// LAB 26: Create MIN HEAP
// ============================================================
/*
 * Min-Heap: parent.value <= children.values
 * Same structure as MaxHeap but comparisons are reversed.
 */
class MinHeap {
    vector<int> heap;

    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent] > heap[i]) {
                swap(heap[parent], heap[i]);
                i = parent;
            } else break;
        }
    }

    void siftDown(int i) {
        int n = heap.size();
        while (true) {
            int smallest = i, l = 2*i+1, r = 2*i+2;
            if (l < n && heap[l] < heap[smallest]) smallest = l;
            if (r < n && heap[r] < heap[smallest]) smallest = r;
            if (smallest == i) break;
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        siftUp(heap.size() - 1);
    }

    int extractMin() {
        if (heap.empty()) { cout << "Heap empty!\n"; return -1; }
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return minVal;
    }

    void display() {
        cout << "Min-Heap array: ";
        for (int v : heap) cout << v << " ";
        cout << "\n";
    }
};

// ============================================================
// LAB 13: HUFFMAN CODING
// ============================================================

/*
 * Huffman Coding – Greedy compression algorithm.
 * Idea: Assign shorter bit codes to more frequent characters.
 *
 * Steps:
 *  1. Count frequency of each character.
 *  2. Build a min-heap (priority queue) of single-node trees.
 *  3. Repeatedly merge two smallest-frequency trees into one.
 *  4. Result: Huffman Tree whose leaves are characters.
 *  5. Assign codes: left edge = '0', right edge = '1'.
 *  6. Encode: replace each character with its bit code.
 *  7. Decode: traverse tree from root using bit string.
 */

struct HuffNode {
    char   ch;
    int    freq;
    HuffNode* left;
    HuffNode* right;
    HuffNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Min-priority queue comparator for HuffNode
struct HuffCmp {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;   // Min-heap: smaller freq has higher priority
    }
};

// ── Build Huffman Tree ──────────────────────────────────────
HuffNode* buildHuffmanTree(const string& text) {
    map<char, int> freq;
    for (char c : text) freq[c]++;          // Count frequencies

    priority_queue<HuffNode*, vector<HuffNode*>, HuffCmp> pq;
    for (auto& p : freq)
        pq.push(new HuffNode(p.first, p.second));

    while (pq.size() > 1) {
        HuffNode* left  = pq.top(); pq.pop();   // Smallest freq
        HuffNode* right = pq.top(); pq.pop();   // Second smallest

        // Internal node – freq = sum of children, ch = '$' (placeholder)
        HuffNode* merged = new HuffNode('$', left->freq + right->freq);
        merged->left  = left;
        merged->right = right;
        pq.push(merged);
    }
    return pq.top();    // Root of Huffman tree
}

// ── Generate codes by traversing tree (left='0', right='1') ─
void generateCodes(HuffNode* node, const string& code, map<char, string>& codes) {
    if (!node) return;
    if (!node->left && !node->right)    // Leaf node – this is a character
        codes[node->ch] = code.empty() ? "0" : code;  // Edge case: single unique char
    generateCodes(node->left,  code + "0", codes);
    generateCodes(node->right, code + "1", codes);
}

// ── Encode text using generated codes ───────────────────────
string huffmanEncode(const string& text, const map<char, string>& codes) {
    string encoded = "";
    for (char c : text) encoded += codes.at(c);
    return encoded;
}

// ── Decode bit string using Huffman Tree ────────────────────
string huffmanDecode(const string& bits, HuffNode* root) {
    string decoded = "";
    HuffNode* curr = root;
    for (char bit : bits) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {  // Reached a leaf
            decoded += curr->ch;
            curr = root;                    // Reset to root for next character
        }
    }
    return decoded;
}


// ============================================================
// ██╗   ██╗███╗   ██╗██╗████████╗   ███████╗
// ██║   ██║████╗  ██║██║╚══██╔══╝   ██╔════╝
// ██║   ██║██╔██╗ ██║██║   ██║      ███████╗
// ██║   ██║██║╚██╗██║██║   ██║      ╚════██║
// ╚██████╔╝██║ ╚████║██║   ██║      ███████║
//  ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝      ╚══════╝
// UNIT 5: SELF-BALANCING TREES
// ============================================================

// ============================================================
// LAB 14: AVL TREE
// ============================================================

/*
 * AVL Tree: A BST where the height difference (Balance Factor)
 * between left and right subtrees of EVERY node is at most 1.
 *
 * Balance Factor (BF) = height(left) - height(right)
 *   BF ∈ {-1, 0, 1}  → balanced
 *   BF = -2 or +2    → unbalanced → requires rotation
 *
 * Rotations:
 *   LL Rotation: Right rotate at unbalanced node  (left-left case)
 *   RR Rotation: Left  rotate at unbalanced node  (right-right case)
 *   LR Rotation: Left rotate left child, then Right rotate node
 *   RL Rotation: Right rotate right child, then Left rotate node
 */

struct AVLNode {
    int data, height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    AVLNode* root;
    AVLTree() : root(nullptr) {}

    // ── Height of node (nullptr = 0) ──────────────────────
    int height(AVLNode* n) { return n ? n->height : 0; }

    // ── Balance Factor = height(left) - height(right) ─────
    int getBalance(AVLNode* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    // ── Update node height ─────────────────────────────────
    void updateHeight(AVLNode* n) {
        if (n) n->height = 1 + max(height(n->left), height(n->right));
    }

    // ── LL Rotation (Right Rotate) ─────────────────────────
    //       y                x
    //      / \              / \
    //     x   T3    →     T1   y
    //    / \                  / \
    //   T1  T2              T2  T3
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x  = y->left;
        AVLNode* T2 = x->right;
        x->right = y;           // Rotation
        y->left  = T2;
        updateHeight(y);
        updateHeight(x);
        cout << "  [AVL] Right rotation at node " << y->data << "\n";
        return x;               // x is new root of this subtree
    }

    // ── RR Rotation (Left Rotate) ──────────────────────────
    //     x                  y
    //    / \                / \
    //   T1   y    →        x   T3
    //       / \           / \
    //      T2  T3        T1  T2
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y  = x->right;
        AVLNode* T2 = y->left;
        y->left  = x;           // Rotation
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        cout << "  [AVL] Left rotation at node " << x->data << "\n";
        return y;
    }

    // ── Balance the node after insert/delete ───────────────
    AVLNode* balance(AVLNode* node) {
        updateHeight(node);
        int bf = getBalance(node);

        // LL Case: left-heavy, left child also left-heavy or balanced
        if (bf > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        // LR Case: left-heavy, left child is right-heavy
        if (bf > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);    // First left rotate child
            return rotateRight(node);               // Then right rotate node
        }

        // RR Case: right-heavy, right child also right-heavy or balanced
        if (bf < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        // RL Case: right-heavy, right child is left-heavy
        if (bf < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right); // First right rotate child
            return rotateLeft(node);                // Then left rotate node
        }

        return node;    // Already balanced
    }

    // ── AVL Insert ────────────────────────────────────────
    AVLNode* insert(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);
        if (key < node->data)       node->left  = insert(node->left,  key);
        else if (key > node->data)  node->right = insert(node->right, key);
        else return node;   // Duplicate – ignore
        return balance(node);
    }

    void insert(int key) {
        root = insert(root, key);
        cout << "  [AVL] Inserted " << key << "\n";
    }

    // ── AVL Delete ────────────────────────────────────────
    AVLNode* deleteNode(AVLNode* node, int key) {
        if (!node) return nullptr;
        if (key < node->data)       node->left  = deleteNode(node->left,  key);
        else if (key > node->data)  node->right = deleteNode(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            // Two children: find inorder successor
            AVLNode* successor = node->right;
            while (successor->left) successor = successor->left;
            node->data  = successor->data;
            node->right = deleteNode(node->right, successor->data);
        }
        return balance(node);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
        cout << "  [AVL] Deleted " << key << "\n";
    }

    void inorder(AVLNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << "(h=" << node->height << ") ";
        inorder(node->right);
    }

    void display() {
        cout << "AVL Inorder: ";
        inorder(root);
        cout << "\n";
    }
};

// ============================================================
// LAB 15: RED-BLACK TREE
// ============================================================

/*
 * Red-Black Tree Properties:
 *  1. Every node is RED or BLACK.
 *  2. Root is always BLACK.
 *  3. Every NULL leaf is BLACK.
 *  4. RED node's children must be BLACK (no two consecutive reds).
 *  5. Every path from node to its NULL descendants has the same
 *     number of BLACK nodes (Black-Height property).
 *
 * Insertion: Always insert as RED, then fix violations.
 * Fix cases depend on uncle's color:
 *  Case 1 (Uncle RED)     : Recolor parent, uncle, grandparent.
 *  Case 2 (Uncle BLACK, triangle) : Rotate to make it Case 3.
 *  Case 3 (Uncle BLACK, line)     : Rotate grandparent + recolor.
 */

enum Color { RED, BLACK };

struct RBNode {
    int data;
    Color color;
    RBNode *left, *right, *parent;
    RBNode(int val) : data(val), color(RED),
                      left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
    RBNode* root;
    RBNode* NIL;    // Sentinel NIL node (BLACK, represents all null leaves)

    // ── Left Rotate ──────────────────────────────────────
    void rotateLeft(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL)         root = y;
        else if (x == x->parent->left) x->parent->left  = y;
        else                           x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // ── Right Rotate ─────────────────────────────────────
    void rotateRight(RBNode* x) {
        RBNode* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL)          root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else                            x->parent->left  = y;
        y->right = x;
        x->parent = y;
    }

    // ── Fix RB violations after insert ────────────────────
    void fixInsert(RBNode* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* uncle = z->parent->parent->right;

                // Case 1: Uncle is RED → recolor
                if (uncle->color == RED) {
                    z->parent->color          = BLACK;
                    uncle->color              = BLACK;
                    z->parent->parent->color  = RED;
                    z = z->parent->parent;
                } else {
                    // Case 2: z is right child → left rotate to make Case 3
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    // Case 3: z is left child → right rotate grandparent
                    z->parent->color         = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            } else {    // Mirror image: parent is right child
                RBNode* uncle = z->parent->parent->left;
                if (uncle->color == RED) {
                    z->parent->color         = BLACK;
                    uncle->color             = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color         = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;    // Property 2: root must be BLACK
    }

    // ── Fix RB violations after delete ───────────────────
    void fixDelete(RBNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBNode* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color  = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            } else {
                RBNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color   = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    // ── Transplant subtrees ───────────────────────────────
    void transplant(RBNode* u, RBNode* v) {
        if (u->parent == NIL)           root = v;
        else if (u == u->parent->left)  u->parent->left  = v;
        else                            u->parent->right = v;
        v->parent = u->parent;
    }

    RBNode* minimum(RBNode* node) {
        while (node->left != NIL) node = node->left;
        return node;
    }

    void inorderHelper(RBNode* node) {
        if (node == NIL) return;
        inorderHelper(node->left);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorderHelper(node->right);
    }

public:
    RedBlackTree() {
        NIL = new RBNode(0);
        NIL->color  = BLACK;
        NIL->left   = NIL->right = NIL->parent = nullptr;
        root = NIL;
    }

    void insert(int key) {
        RBNode* z = new RBNode(key);
        z->left = z->right = z->parent = NIL;

        RBNode* y = NIL, *x = root;
        while (x != NIL) {
            y = x;
            x = (z->data < x->data) ? x->left : x->right;
        }
        z->parent = y;
        if (y == NIL)          root = z;
        else if (z->data < y->data) y->left  = z;
        else                        y->right = z;

        fixInsert(z);
        cout << "  [RBT] Inserted " << key << "\n";
    }

    void deleteNode(int key) {
        RBNode* z = root;
        while (z != NIL && z->data != key)
            z = (key < z->data) ? z->left : z->right;
        if (z == NIL) { cout << "  [RBT] " << key << " not found.\n"; return; }

        RBNode* y = z;
        RBNode* x;
        Color origColor = y->color;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            origColor = y->color;
            x = y->right;
            if (y->parent == z) x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (origColor == BLACK) fixDelete(x);
        cout << "  [RBT] Deleted " << key << "\n";
    }

    void display() {
        cout << "RBT Inorder (R=Red, B=Black): ";
        inorderHelper(root);
        cout << "\n";
    }
};


// ============================================================
// ██╗   ██╗███╗   ██╗██╗████████╗   ██████╗
// ██║   ██║████╗  ██║██║╚══██╔══╝  ██╔════╝
// ██║   ██║██╔██╗ ██║██║   ██║     ███████╗
// ██║   ██║██║╚██╗██║██║   ██║     ██╔═══██╗
// ╚██████╔╝██║ ╚████║██║   ██║     ╚██████╔╝
//  ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝      ╚═════╝
// UNIT 6: GRAPH REPRESENTATION & TRAVERSAL
// ============================================================

/*
 * Graph Representation: Adjacency List (using vector<vector<int>>)
 * Operations: Create, Insert Vertex, Delete Vertex, Traverse
 * Traversals: BFS (uses Queue), DFS (uses Stack or Recursion)
 */

// ============================================================
// LAB 16: Graph Operations
// ============================================================

class Graph {
public:
    int V;                              // Number of vertices
    vector<vector<int>> adjList;        // Adjacency list
    bool directed;

    Graph(int v, bool dir = false) : V(v), directed(dir) {
        adjList.resize(V);
    }

    // ── Insert Edge between u and v ──────────────────────
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        if (!directed) adjList[v].push_back(u);  // Undirected: add both ways
        cout << "  [GRAPH] Edge added: " << u << " → " << v << "\n";
    }

    // ── Delete Edge between u and v ──────────────────────
    void deleteEdge(int u, int v) {
        adjList[u].erase(remove(adjList[u].begin(), adjList[u].end(), v), adjList[u].end());
        if (!directed)
            adjList[v].erase(remove(adjList[v].begin(), adjList[v].end(), u), adjList[v].end());
        cout << "  [GRAPH] Edge deleted: " << u << " ↔ " << v << "\n";
    }

    // ── Insert Vertex (add new vertex with no edges) ─────
    void addVertex() {
        adjList.push_back(vector<int>());
        V++;
        cout << "  [GRAPH] Vertex " << V-1 << " added. Total vertices: " << V << "\n";
    }

    // ── Delete Vertex (remove vertex and all its edges) ──
    void deleteVertex(int v) {
        adjList.erase(adjList.begin() + v);
        V--;
        // Remove all edges pointing to deleted vertex, adjust indices
        for (auto& neighbors : adjList) {
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), v), neighbors.end());
            for (int& nb : neighbors) if (nb > v) nb--;  // Shift indices down
        }
        cout << "  [GRAPH] Vertex " << v << " deleted. Total vertices: " << V << "\n";
    }

    // ── Display adjacency list ────────────────────────────
    void display() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < V; i++) {
            cout << "  " << i << " → ";
            for (int nb : adjList[i]) cout << nb << " ";
            cout << "\n";
        }
    }
};

// ============================================================
// LAB 17: BFS – Breadth First Search
// ============================================================

/*
 * BFS Algorithm:
 *  1. Start at source, mark as visited, enqueue it.
 *  2. While queue not empty:
 *       a. Dequeue front vertex, VISIT it.
 *       b. Enqueue all unvisited neighbors, mark them visited.
 * BFS explores level by level (uses QUEUE).
 * Application: Shortest path (unweighted), connected components.
 */
void BFS(const Graph& g, int start) {
    vector<bool> visited(g.V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS from vertex " << start << ": ";
    while (!q.empty()) {
        int v = q.front(); q.pop();
        cout << v << " ";
        for (int nb : g.adjList[v]) {
            if (!visited[nb]) {
                visited[nb] = true;
                q.push(nb);
            }
        }
    }
    cout << "\n";
}

// ============================================================
// LAB 18: DFS – Depth First Search
// ============================================================

/*
 * DFS Algorithm (using explicit stack, non-recursive):
 *  1. Push start vertex onto stack.
 *  2. While stack not empty:
 *       a. Pop vertex. If not visited: VISIT it, mark visited.
 *       b. Push all unvisited neighbors (in reverse order for consistency).
 * DFS goes as deep as possible before backtracking.
 * Application: Topological sort, cycle detection, connected components.
 */
void DFS(const Graph& g, int start) {
    vector<bool> visited(g.V, false);
    stack<int> st;
    st.push(start);

    cout << "DFS from vertex " << start << ": ";
    while (!st.empty()) {
        int v = st.top(); st.pop();
        if (!visited[v]) {
            cout << v << " ";
            visited[v] = true;
            // Push neighbors in reverse so leftmost is processed first
            for (int i = g.adjList[v].size() - 1; i >= 0; i--)
                if (!visited[g.adjList[v][i]])
                    st.push(g.adjList[v][i]);
        }
    }
    cout << "\n";
}


// ============================================================
// ██╗   ██╗███╗   ██╗██╗████████╗   ███████╗
// ██║   ██║████╗  ██║██║╚══██╔══╝   ╚════██╗
// ██║   ██║██╔██╗ ██║██║   ██║           ██║
// ██║   ██║██║╚██╗██║██║   ██║          ██╔╝
// ╚██████╔╝██║ ╚████║██║   ██║         ██║
//  ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝         ╚═╝
// UNIT 7: GRAPH PATH ALGORITHMS
// ============================================================

// ============================================================
// LAB 19: WARSHALL'S ALGORITHM (Transitive Closure)
// ============================================================

/*
 * Warshall's Algorithm computes the TRANSITIVE CLOSURE of a graph.
 * reach[i][j] = 1 means there EXISTS a path from i to j.
 *
 * Algorithm (DP):
 *   For each intermediate vertex k:
 *     For each pair (i, j):
 *       If path i→k exists AND path k→j exists → path i→j exists.
 *
 * Time: O(V³)
 */
void warshall(vector<vector<int>> reach, int V) {
    // reach starts as adjacency matrix (1 if direct edge exists)
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (reach[i][k] && reach[k][j])
                    reach[i][j] = 1;    // Path found through k

    cout << "Transitive Closure Matrix (Warshall):\n";
    cout << "     ";
    for (int j = 0; j < V; j++) cout << setw(3) << j;
    cout << "\n";
    for (int i = 0; i < V; i++) {
        cout << setw(3) << i << ": ";
        for (int j = 0; j < V; j++) cout << setw(3) << reach[i][j];
        cout << "\n";
    }
}

// ============================================================
// LAB 20: FLOYD-WARSHALL ALGORITHM (All-Pairs Shortest Path)
// ============================================================

/*
 * Floyd-Warshall finds the SHORTEST DISTANCE between ALL pairs of vertices.
 *
 * Algorithm (DP):
 *   dist[i][j] = min distance from i to j.
 *   Initialize: dist[i][j] = edge weight if direct edge, else INF; dist[i][i]=0.
 *   For each intermediate vertex k:
 *     For each pair (i, j):
 *       dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 *
 * Time: O(V³)
 */
const int INF_DIST = 1e9;

void floydWarshall(vector<vector<int>> dist, int V) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] != INF_DIST && dist[k][j] != INF_DIST)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    cout << "All-Pairs Shortest Path (Floyd-Warshall):\n";
    cout << "     ";
    for (int j = 0; j < V; j++) cout << setw(6) << j;
    cout << "\n";
    for (int i = 0; i < V; i++) {
        cout << setw(3) << i << ": ";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF_DIST) cout << setw(6) << "INF";
            else                         cout << setw(6) << dist[i][j];
        }
        cout << "\n";
    }
}

// ============================================================
// LAB 21: DIJKSTRA'S ALGORITHM (Single-Source Shortest Path)
// ============================================================

/*
 * Dijkstra's Algorithm finds the shortest path from a single SOURCE
 * to all other vertices in a weighted graph (non-negative weights).
 *
 * Algorithm (Greedy + Min-Heap):
 *  1. Initialize dist[source]=0, all others=INF.
 *  2. Use a min-priority queue (vertex, dist).
 *  3. Greedily pick the unvisited vertex with smallest distance.
 *  4. Relax all its neighbors: if dist[u]+w < dist[v] → update dist[v].
 *
 * Time: O((V + E) log V) with min-heap.
 */
void dijkstra(int src, int V, const vector<vector<pair<int,int>>>& adj) {
    vector<int> dist(V, INF_DIST);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq; // min-heap

    dist[src] = 0;
    pq.push({0, src});  // {distance, vertex}

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;  // Outdated entry – skip

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Dijkstra's Shortest Paths from vertex " << src << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "  " << src << " → " << i << " : ";
        if (dist[i] == INF_DIST) cout << "INF\n";
        else                      cout << dist[i] << "\n";
    }
}


// ============================================================
// ██╗   ██╗███╗   ██╗██╗████████╗   █████╗
// ██║   ██║████╗  ██║██║╚══██╔══╝  ██╔══██╗
// ██║   ██║██╔██╗ ██║██║   ██║     ╚█████╔╝
// ██║   ██║██║╚██╗██║██║   ██║     ██╔══██╗
// ╚██████╔╝██║ ╚████║██║   ██║     ╚█████╔╝
//  ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝      ╚════╝
// UNIT 8: OPTIMIZATION PROBLEMS
// ============================================================

// ============================================================
// LAB 22: TRAVELLING SALESMAN PROBLEM (TSP)
// ============================================================

/*
 * TSP: Given N cities and distances between every pair,
 * find the MINIMUM COST Hamiltonian cycle (visit each city
 * exactly once and return to start).
 *
 * Approach: Dynamic Programming with bitmask (Held-Karp Algorithm)
 *   dp[mask][i] = min cost to visit all cities in 'mask', ending at city i.
 *   mask is a bitmask: bit j is 1 if city j has been visited.
 *
 * Time: O(2^N × N²)  – feasible for small N (≤ 20).
 */
void TSP(const vector<vector<int>>& dist, int N) {
    // dp[mask][i] = min cost to reach city i having visited cities in mask
    vector<vector<int>> dp(1 << N, vector<int>(N, INF_DIST));
    dp[1][0] = 0;   // Start at city 0 (bit 0 set in mask)

    for (int mask = 1; mask < (1 << N); mask++) {
        for (int u = 0; u < N; u++) {
            if (!(mask & (1 << u))) continue;   // u not in current tour
            if (dp[mask][u] == INF_DIST) continue;

            for (int v = 0; v < N; v++) {
                if (mask & (1 << v)) continue;  // v already visited
                int newMask = mask | (1 << v);
                dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + dist[u][v]);
            }
        }
    }

    int fullMask = (1 << N) - 1;   // All cities visited
    int ans = INF_DIST;
    for (int i = 1; i < N; i++)    // Return from any city back to 0
        if (dp[fullMask][i] != INF_DIST)
            ans = min(ans, dp[fullMask][i] + dist[i][0]);

    cout << "TSP Minimum Tour Cost: " << ans << "\n";
}

// ============================================================
// LAB 23: FRACTIONAL KNAPSACK PROBLEM
// ============================================================

/*
 * Fractional Knapsack: We can take FRACTIONS of items.
 * Greedy Approach: Sort by value/weight ratio (descending).
 *   Take as much of the highest-ratio item as possible,
 *   then the next, until knapsack is full.
 *
 * Time: O(N log N) due to sorting.
 */
void fractionalKnapsack(int W, vector<int>& weights, vector<int>& values, int N) {
    // Create (ratio, index) pairs and sort by ratio descending
    vector<pair<double, int>> ratios(N);
    for (int i = 0; i < N; i++)
        ratios[i] = {(double)values[i] / weights[i], i};
    sort(ratios.rbegin(), ratios.rend());

    double totalValue = 0.0;
    int remaining = W;

    cout << "Fractional Knapsack (Capacity = " << W << "):\n";
    for (auto& [ratio, idx] : ratios) {
        if (remaining == 0) break;
        int take = min(weights[idx], remaining);
        double val = take * ratio;
        totalValue += val;
        remaining  -= take;
        cout << "  Item " << idx << " → Take " << take << "/" << weights[idx]
             << " units, Value gained = " << fixed << setprecision(2) << val << "\n";
    }
    cout << "  Total Value = " << fixed << setprecision(2) << totalValue << "\n";
}

// ============================================================
// LAB 24: 0/1 KNAPSACK PROBLEM
// ============================================================

/*
 * 0/1 Knapsack: Each item is either taken COMPLETELY or not at all.
 * Dynamic Programming Approach:
 *   dp[i][w] = max value using first i items with capacity w.
 *   Recurrence:
 *     If weight[i] > w: dp[i][w] = dp[i-1][w]         (can't take item i)
 *     Else:             dp[i][w] = max(dp[i-1][w],     (skip item i)
 *                                      dp[i-1][w-weight[i]] + value[i]) (take it)
 *
 * Time: O(N × W)   Space: O(N × W)
 */
void knapsack01(int W, vector<int>& weights, vector<int>& values, int N) {
    // dp[i][w] = max value with first i items, capacity w
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i-1][w];     // Don't take item i
            if (weights[i-1] <= w)
                dp[i][w] = max(dp[i][w], dp[i-1][w - weights[i-1]] + values[i-1]);
        }
    }

    cout << "0/1 Knapsack (Capacity = " << W << "):\n";
    cout << "  Maximum Value = " << dp[N][W] << "\n";

    // Trace back to find which items were selected
    cout << "  Items selected: ";
    int w = W;
    for (int i = N; i > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {  // Item i was taken
            cout << i << " (w=" << weights[i-1] << ", v=" << values[i-1] << ") ";
            w -= weights[i-1];
        }
    }
    cout << "\n";
}


// ============================================================
//  ███╗   ███╗ █████╗ ██╗███╗   ██╗
//  ████╗ ████║██╔══██╗██║████╗  ██║
//  ██╔████╔██║███████║██║██╔██╗ ██║
//  ██║╚██╔╝██║██╔══██║██║██║╚██╗██║
//  ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
//  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝
// ============================================================

int main() {

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║         ADVANCED ALGORITHMS – ALL UNIT LAB SOLUTIONS        ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";

    // ═════════════════════════════════════════════════════════════
    // UNIT 1: BINARY TREE & BST
    // ═════════════════════════════════════════════════════════════
    printSeparator("UNIT 1 | LAB 1: Binary Tree Construction");
    {
        BinaryTree bt;
        cout << "Inserting: 1 2 3 4 5 6 7\n";
        for (int v : {1, 2, 3, 4, 5, 6, 7}) bt.insert(v);
        bt.display();
    }

    printSeparator("UNIT 1 | LAB 2: BST – FIND & INSERT");
    {
        BST bst;
        cout << "Inserting into BST:\n";
        for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
        bst.display();
        cout << "\nSearch Operations:\n";
        bst.find(40);
        bst.find(99);
    }

    // ═════════════════════════════════════════════════════════════
    // UNIT 2: TREE TRAVERSALS
    // ═════════════════════════════════════════════════════════════
    printSeparator("UNIT 2 | LAB 3-8: Tree Traversals");
    {
        // Build a BST for traversal demos
        BST bst;
        for (int v : {4, 2, 6, 1, 3, 5, 7}) bst.insert(v);
        TreeNode* r = bst.root;

        cout << "\n[Stack-Based Traversals]\n";
        cout << "Preorder  (Stack): "; preorderStack(r);  cout << "\n";
        cout << "Inorder   (Stack): "; inorderStack(r);   cout << "\n";
        cout << "Postorder (Stack): "; postorderStack(r); cout << "\n";

        cout << "\n[Recursive Traversals]\n";
        cout << "Preorder  (Recursive): "; preorderRecursive(r);  cout << "\n";
        cout << "Inorder   (Recursive): "; inorderRecursive(r);   cout << "\n";
        cout << "Postorder (Recursive): "; postorderRecursive(r); cout << "\n";
    }

    // ═════════════════════════════════════════════════════════════
    // UNIT 3: BST DELETION
    // ═════════════════════════════════════════════════════════════
    printSeparator("UNIT 3 | LAB 9-11: BST Deletion");
    {
        BST bst;
        for (int v : {50, 30, 70, 20, 40, 60, 80, 35}) bst.insert(v);
        cout << "\nBefore deletions:\n"; bst.display();

        cout << "\nLab 9  – Delete LEAF node (20 – no children):\n";
        bst.root = deleteBST(bst.root, 20);

        cout << "\nLab 10 – Delete node with ONE child (30 – only right child 40 remains):\n";
        bst.root = deleteBST(bst.root, 30);

        cout << "\nLab 11 – Delete node with TWO children (50 – root):\n";
        bst.root = deleteBST(bst.root, 50);

        cout << "\nAfter deletions:\n"; bst.display();
    }

    // ═════════════════════════════════════════════════════════════
    // UNIT 4: HEAP & GREEDY/CODING ALGORITHMS
    // ═════════════════════════════════════════════════════════════
    printSeparator("UNIT 4 | LAB 12: Heap Sort");
    {
        vector<int> arr = {64, 25, 12, 22, 11, 90, 45};
        cout << "Before: ";
        for (int x : arr) cout << x << " ";
        heapSort(arr);
        cout << "\nAfter Heap Sort: ";
        for (int x : arr) cout << x << " ";
        cout << "\n";
    }

    printSeparator("UNIT 4 | LAB 25: Max Heap");
    {
        MaxHeap mxh;
        for (int v : {10, 20, 15, 40, 50, 100, 25}) mxh.insert(v);
        mxh.display();
        cout << "Extract Max: " << mxh.extractMax() << "\n";
        mxh.display();
    }

    printSeparator("UNIT 4 | LAB 26: Min Heap");
    {
        MinHeap mnh;
        for (int v : {10, 20, 15, 40, 50, 100, 25}) mnh.insert(v);
        mnh.display();
        cout << "Extract Min: " << mnh.extractMin() << "\n";
        mnh.display();
    }

    printSeparator("UNIT 4 | LAB 13: Huffman Coding");
    {
        string text = "huffman coding algorithm";
        cout << "Original Text : \"" << text << "\"\n";
        cout << "Length        : " << text.size() << " chars = " << text.size()*8 << " bits\n";

        HuffNode* tree = buildHuffmanTree(text);
        map<char, string> codes;
        generateCodes(tree, "", codes);

        cout << "\nHuffman Codes:\n";
        for (auto& [ch, code] : codes)
            cout << "  '" << ch << "' → " << code << "\n";

        string encoded = huffmanEncode(text, codes);
        cout << "\nEncoded bits  : " << encoded << "\n";
        cout << "Encoded length: " << encoded.size() << " bits\n";

        string decoded = huffmanDecode(encoded, tree);
        cout << "Decoded text  : \"" << decoded << "\"\n";
        cout << "Compression   : " << fixed << setprecision(1)
             << (1.0 - (double)encoded.size() / (text.size() * 8)) * 100 << "%\n";
    }

    // ═════════════════════════════════════════════════════════════
    // UNIT 5: SELF-BALANCING TREES
    // ═════════════════════════════════════════════════════════════
    printSeparator("UNIT 5 | LAB 14: AVL Tree");
    {
        AVLTree avl;
        cout << "Inserting: 10 20 30 (RR case), 25, 5\n";
        for (int v : {10, 20, 30, 25, 5}) avl.insert(v);
        avl.display();
        cout << "\nInserting 15 (LR case):\n";
        avl.insert(15);
        avl.display();
        cout << "\nDeleting 20:\n";
        avl.deleteNode(20);
        avl.display();
    }

    printSeparator("UNIT 5 | LAB 15: Red-Black Tree");
    {
        RedBlackTree rbt;
        cout << "Inserting: 10 20 30 15 25 5 1\n";
        for (int v : {10, 20, 30, 15, 25, 5, 1}) rbt.insert(v);
        rbt.display();
        cout << "\nDeleting 20:\n";
        rbt.deleteNode(20);
        rbt.display();
    }

    // ═════════════════════════════════════════════════════════════
    // UNIT 6: GRAPH OPERATIONS & TRAVERSAL
    // ═════════════════════════════════════════════════════════════
    printSeparator("UNIT 6 | LAB 16: Graph Operations");
    {
        Graph g(5, false);  // 5 vertices, undirected
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        g.addEdge(3, 4);
        cout << "\n"; g.display();

        cout << "\nAdding new vertex:\n";
        g.addVertex();
        g.addEdge(5, 0);
        g.display();
    }

    printSeparator("UNIT 6 | LAB 17 & 18: BFS and DFS");
    {
        Graph g(6, false);
        g.addEdge(0, 1); g.addEdge(0, 2); g.addEdge(1, 3);
        g.addEdge(1, 4); g.addEdge(2, 5);
        cout << "\n"; g.display();
        cout << "\n"; BFS(g, 0);
        DFS(g, 0);
    }

    // ═════════════════════════════════════════════════════════════
    // UNIT 7: GRAPH PATH ALGORITHMS
    // ═════════════════════════════════════════════════════════════
    printSeparator("UNIT 7 | LAB 19: Warshall's Algorithm");
    {
        int V = 4;
        // Adjacency matrix: 1 = direct edge, 0 = no edge
        vector<vector<int>> reach = {
            {1, 1, 0, 1},
            {0, 1, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 1}
        };
        warshall(reach, V);
    }

    printSeparator("UNIT 7 | LAB 20: Floyd-Warshall Algorithm");
    {
        int V = 4;
        auto I = INF_DIST;
        vector<vector<int>> dist = {
            {0, 3, I, 7},
            {8, 0, 2, I},
            {5, I, 0, 1},
            {2, I, I, 0}
        };
        floydWarshall(dist, V);
    }

    printSeparator("UNIT 7 | LAB 21: Dijkstra's Shortest Path");
    {
        int V = 5;
        // adj[u] = list of {v, weight}
        vector<vector<pair<int,int>>> adj(V);
        auto addWEdge = [&](int u, int v, int w) {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        };
        addWEdge(0, 1, 10); addWEdge(0, 2,  3);
        addWEdge(1, 2,  1); addWEdge(1, 3,  2);
        addWEdge(2, 1,  4); addWEdge(2, 3,  8);
        addWEdge(2, 4,  2); addWEdge(3, 4,  5);
        dijkstra(0, V, adj);
    }

    // ═════════════════════════════════════════════════════════════
    // UNIT 8: OPTIMIZATION PROBLEMS
    // ═════════════════════════════════════════════════════════════
    printSeparator("UNIT 8 | LAB 22: Travelling Salesman Problem (TSP)");
    {
        int N = 4;
        vector<vector<int>> dist = {
            { 0, 10, 15, 20},
            {10,  0, 35, 25},
            {15, 35,  0, 30},
            {20, 25, 30,  0}
        };
        TSP(dist, N);
    }

    printSeparator("UNIT 8 | LAB 23: Fractional Knapsack");
    {
        int W = 50;
        vector<int> weights = {10, 20, 30};
        vector<int> values  = {60, 100, 120};
        int N = weights.size();
        fractionalKnapsack(W, weights, values, N);
    }

    printSeparator("UNIT 8 | LAB 24: 0/1 Knapsack");
    {
        int W = 50;
        vector<int> weights = {10, 20, 30};
        vector<int> values  = {60, 100, 120};
        int N = weights.size();
        knapsack01(W, weights, values, N);
    }

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║           ALL LAB PROBLEMS EXECUTED SUCCESSFULLY!           ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    return 0;
}

/*
================================================================================
  QUICK REFERENCE – ALGORITHM COMPLEXITY SUMMARY
================================================================================

  UNIT 1 – Trees
  ──────────────────────────────────────────────────────────────────────────────
  Binary Tree Insert (Level-order)       : O(N)
  BST Find / Insert                      : O(h)   avg O(log N), worst O(N)

  UNIT 2 – Traversals
  ──────────────────────────────────────────────────────────────────────────────
  All Traversals (Stack & Recursive)     : O(N) time, O(h) space

  UNIT 3 – BST Deletion
  ──────────────────────────────────────────────────────────────────────────────
  BST Delete                             : O(h)   avg O(log N), worst O(N)

  UNIT 4 – Heap & Huffman
  ──────────────────────────────────────────────────────────────────────────────
  Heap Sort                              : O(N log N) time, O(1) space
  Max/Min Heap Insert                    : O(log N)
  Max/Min Heap Extract                   : O(log N)
  Huffman Coding                         : O(N log N)

  UNIT 5 – Self-Balancing Trees
  ──────────────────────────────────────────────────────────────────────────────
  AVL Tree Insert/Delete                 : O(log N) guaranteed
  Red-Black Tree Insert/Delete           : O(log N) guaranteed

  UNIT 6 – Graph Traversal
  ──────────────────────────────────────────────────────────────────────────────
  BFS / DFS                              : O(V + E)

  UNIT 7 – Shortest Path
  ──────────────────────────────────────────────────────────────────────────────
  Warshall's Algorithm                   : O(V³)
  Floyd-Warshall Algorithm               : O(V³)
  Dijkstra's Algorithm                   : O((V + E) log V)

  UNIT 8 – Optimization
  ──────────────────────────────────────────────────────────────────────────────
  TSP (Held-Karp DP)                     : O(2^N × N²)
  Fractional Knapsack                    : O(N log N)
  0/1 Knapsack (DP)                      : O(N × W)

================================================================================
*/
