#include <iostream>
using namespace std;

// Structure representing a node in the binary search tree
struct NodeStru {
    int data;              // Data stored in the node
    NodeStru* left;        // Pointer to the left child
    NodeStru* right;       // Pointer to the right child

    // Constructor to initialize a new node
    NodeStru(int val) {
        data = val;        // Assign the given value to the node's data
        left = right = nullptr;  // Set left and right children to nullptr
    }
};

// Function to insert a new node into the BST
NodeStru* BSTInsertion(NodeStru* newNode, NodeStru* RootNode) {
    // Base case: If the tree is empty, return the new node
    if (RootNode == nullptr)
        return newNode;

    // Recursive case: Insert the node in the correct position in the tree
    if (newNode->data < RootNode->data)
        // Insert in the left subtree if the new node's data is smaller
        RootNode->left = BSTInsertion(newNode, RootNode->left);
    else if (newNode->data > RootNode->data)
        // Insert in the right subtree if the new node's data is greater
        RootNode->right = BSTInsertion(newNode, RootNode->right);

    // Return the root node (unchanged)
    return RootNode;
}

// Helper function to find the minimum value node in a subtree
NodeStru* findMin(NodeStru* node) {
    // The leftmost node is the smallest node in a BST
    while (node->left != nullptr)
        node = node->left;
    return node;
}

// Function to delete a node from the BST
NodeStru* BSTDeletion(NodeStru* RootNode, int key) {
    // Base case: If the tree is empty, return nullptr
    if (RootNode == nullptr)
        return RootNode;

    // Recursive case: Traverse the tree to find the node to delete
    if (key < RootNode->data)
        // Key is smaller, so move to the left subtree
        RootNode->left = BSTDeletion(RootNode->left, key);
    else if (key > RootNode->data)
        // Key is larger, so move to the right subtree
        RootNode->right = BSTDeletion(RootNode->right, key);
    else {
        // Node found (RootNode->data == key), handle the deletion

        // Case 1: Node has only one child or no child
        if (RootNode->left == nullptr) {
            NodeStru* temp = RootNode->right;  // Get the right child
            delete RootNode;                   // Delete the current node
            return temp;                       // Return the right child
        }
        else if (RootNode->right == nullptr) {
            NodeStru* temp = RootNode->left;   // Get the left child
            delete RootNode;                   // Delete the current node
            return temp;                       // Return the left child
        }

        // Case 2: Node has two children
        // Get the inorder successor (smallest node in the right subtree)
        NodeStru* temp = findMin(RootNode->right);

        // Replace the current node's data with the inorder successor's data
        RootNode->data = temp->data;

        // Delete the inorder successor (recursive call)
        RootNode->right = BSTDeletion(RootNode->right, temp->data);
    }

    // Return the updated root node
    return RootNode;
}

// Function to perform an in-order traversal of the tree
// In-order traversal visits nodes in ascending order (left, root, right)
void inorderTraversal(NodeStru* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);     // Traverse the left subtree
        cout << root->data << " ";        // Visit the root node (print data)
        inorderTraversal(root->right);    // Traverse the right subtree
    }
}

int main() {
    NodeStru* root = nullptr;  // Initialize the root of the tree to nullptr (empty tree)

    // Insertion examples
    root = BSTInsertion(new NodeStru(50), root);  // Insert node with value 50
    root = BSTInsertion(new NodeStru(30), root);  // Insert node with value 30
    root = BSTInsertion(new NodeStru(20), root);  // Insert node with value 20
    root = BSTInsertion(new NodeStru(40), root);  // Insert node with value 40
    root = BSTInsertion(new NodeStru(70), root);  // Insert node with value 70
    root = BSTInsertion(new NodeStru(60), root);  // Insert node with value 60
    root = BSTInsertion(new NodeStru(80), root);  // Insert node with value 80

    // Print the tree before deletion (in-order traversal)
    cout << "In-order traversal before deletion: ";
    inorderTraversal(root);
    cout << endl;

    // Deletion example
    root = BSTDeletion(root, 50);  // Delete the node with value 50

    // Print the tree after deletion (in-order traversal)
    cout << "In-order traversal after deletion: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
