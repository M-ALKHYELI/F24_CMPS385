#include <iostream>
using namespace std;

// Define the structure of each node in the tree
struct TreeNode {
    int data;           // Holds the value of the node
    TreeNode* left;     // Pointer to the left child
    TreeNode* right;    // Pointer to the right child

    // Constructor to initialize node with a value and null children
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Function for Depth-First Traversal (Inorder Traversal)
void depthFirstTraversal(TreeNode* root) {
    if (root == nullptr) return; // Base case: if tree is empty, do nothing

    // Recursive Inorder traversal: Left, Root, Right
    depthFirstTraversal(root->left);  // Process left subtree
    cout << root->data << " ";        // Visit root node
    depthFirstTraversal(root->right); // Process right subtree
}

int main() {
    // Construct a sample binary tree for demonstration
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    // Perform Depth-First Traversal
    cout << "Depth-First Traversal (Inorder): ";
    depthFirstTraversal(root);
    cout << endl;

    return 0;
}
