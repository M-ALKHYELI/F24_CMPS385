#include <iostream>
#include <queue> // Include queue for BFT
using namespace std;

// Define the structure of each node in the tree
struct TreeNode {
    int data;           // Holds the value of the node
    TreeNode* left;     // Pointer to the left child
    TreeNode* right;    // Pointer to the right child

    // Constructor to initialize node with a value and null children
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Function for Breadth-First Traversal (BFT)
void breadthFirstTraversal(TreeNode* root) {
    if (root == nullptr) return; // Base case: if tree is empty, do nothing

    // Queue to manage the nodes at each level
    queue<TreeNode*> q;
    q.push(root); // Start with the root node in the queue

    // Continue processing nodes until the queue is empty
    while (!q.empty()) {
        // Get the node at the front of the queue
        TreeNode* current = q.front();
        q.pop(); // Remove the processed node from the queue

        // Print the node’s data (processed in order of levels)
        cout << current->data << " ";

        // If the node has a left child, add it to the queue
        if (current->left != nullptr) q.push(current->left);

        // If the node has a right child, add it to the queue
        if (current->right != nullptr) q.push(current->right);
    }
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

    // Perform Breadth-First Traversal
    cout << "Breadth-First Traversal: ";
    breadthFirstTraversal(root);
    cout << endl;

    return 0;
}
