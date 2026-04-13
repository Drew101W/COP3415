// File: AVL_countGreaterNodeWhiting.cpp
// Name: Drew Whiting
// Course: COP3415.02I&T
// Date of Last Modification: April 13, 2026

#include <iostream>
using namespace std;

// AVL tree node
struct Node {
    int value;
    Node *left, *right;
    int height;
};

// Returns the height of a node, or 0 if the node is null
// Parameters:
//   N - pointer to a tree node (may be nullptr)
// Returns: integer height of the node, 0 if null
int height(Node *N) {
    // A null node has height 0
    if (N == nullptr)
        return 0;
    return N->height;
}

// Computes the balance factor of a node (left height minus right height)
// Parameters:
//   N - pointer to a tree node (may be nullptr)
// Returns: balance factor as an integer; 0 if node is null
int getBalance(Node *N) {
    // A null node is perfectly balanced
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Creates and returns a new leaf node with the given value
// Parameters:
//   value - integer value to store in the new node
// Returns: pointer to the newly allocated node
Node* newNode(int value) {
    Node* node = new Node();
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // New node starts as a leaf (height 1)
    return node;
}

// Performs a right rotation on the subtree rooted at y
// Parameters:
//   y - pointer to the root of the subtree to rotate
// Returns: pointer to the new root of the rotated subtree
Node *rightRotate(Node *y) {
    Node *x = y->left;   // x becomes the new root
    Node *T2 = x->right; // T2 is x's right subtree, will move to y's left

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights bottom-up (y first, then x since x is now above y)
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // x is the new root
}

// Performs a left rotation on the subtree rooted at x
// Parameters:
//   x - pointer to the root of the subtree to rotate
// Returns: pointer to the new root of the rotated subtree
Node *leftRotate(Node *x) {
    Node *y = x->right;  // y becomes the new root
    Node *T2 = y->left;  // T2 is y's left subtree, will move to x's right

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights bottom-up (x first, then y since y is now above x)
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // y is the new root
}

// Inserts a value into the AVL tree and rebalances if necessary
// Parameters:
//   node  - pointer to the current subtree root (may be nullptr)
//   value - integer value to insert
// Returns: pointer to the updated subtree root after insertion and rebalancing
Node* insert(Node* node, int value) {
    // Standard BST insertion
    if (node == nullptr)
        return newNode(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else
        return node; // Duplicate values are not inserted

    // Update height of this ancestor node
    node->height = max(height(node->left), height(node->right)) + 1;

    // Check balance factor to detect imbalance
    int balance = getBalance(node);

    // Left-Left case: single right rotation
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    // Right-Right case: single left rotation
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    // Left-Right case: left rotate left child, then right rotate current
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left case: right rotate right child, then left rotate current
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // No rebalancing needed
}

// Counts how many nodes in the AVL tree have a value strictly greater than the given value
// Parameters:
//   node  - pointer to the current subtree root (may be nullptr)
//   value - the threshold; nodes strictly greater than this are counted
// Returns: integer count of nodes with value > the given threshold
int countGreaterNodes(Node *node, int value) {
    // Base case: empty subtree contributes 0
    if (node == nullptr)
        return 0;

    if (node->value > value) {
        // Current node qualifies; all nodes in the right subtree also qualify
        // (since AVL is a BST, right subtree values > node->value > value)
        // Also recurse left because there may be more qualifying nodes there
        return 1
             + countGreaterNodes(node->right, value)
             + countGreaterNodes(node->left, value);
    } else {
        // Current node does not qualify; only the right subtree can have larger values
        return countGreaterNodes(node->right, value);
    }
}

int main() {
    Node *root = nullptr;

    // Construct AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 30);

    // Count nodes greater than 15
    int key = 15;
    cout << "Number of nodes greater than " << key << ": "
         << countGreaterNodes(root, key) << endl;

    return 0;
}