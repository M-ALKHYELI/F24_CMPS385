#include <iostream>
#include <algorithm>  // For max function
using namespace std;

// AVL Tree Node Structure
struct AVLNode {
    int data;             // Data stored in the node
    AVLNode* left;        // Pointer to the left child
    AVLNode* right;       // Pointer to the right child
    int height;           // Height of the node in the AVL tree
};

// Helper function to get the height of a node
int height(AVLNode* N) {
    if (N == nullptr)
        return 0;  // Return height 0 for null nodes
    return N->height;  // Return the height of the node
}

// Helper function to create a new AVL node
AVLNode* newNode(int data) {
    AVLNode* node = new AVLNode(); // Allocate memory for the new node
    node->data = data;             // Set the data value
    node->left = nullptr;          // Initialize left child as null
    node->right = nullptr;         // Initialize right child as null
    node->height = 1;              // Set height as 1 (new node is added at the leaf)
    return node;
}

// Utility function to right rotate the subtree rooted with y
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;          // Set x as left child of y
    AVLNode* T2 = x->right;        // T2 is the right child of x

    // Perform rotation
    x->right = y;                  // Make y the right child of x
    y->left = T2;                  // Update y's left child to be T2

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Utility function to left rotate the subtree rooted with x
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;         // Set y as the right child of x
    AVLNode* T2 = y->left;         // T2 is the left child of y

    // Perform rotation
    y->left = x;                   // Make x the left child of y
    x->right = T2;                 // Update x's right child to be T2

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get balance factor of a node N
int getBalance(AVLNode* N) {
    if (N == nullptr)
        return 0;  // Return balance factor 0 for null nodes
    return height(N->left) - height(N->right);  // Difference in heights of left and right subtrees
}

// Function to insert a key into the AVL tree
AVLNode* insertAVL(AVLNode* node, int key) {
    // Perform normal BST insertion
    if (node == nullptr)
        return(newNode(key));  // Insert new node if current node is null

    if (key < node->data)      // Insert into the left subtree if the key is smaller
        node->left = insertAVL(node->left, key);
    else if (key > node->data) // Insert into the right subtree if the key is larger
        node->right = insertAVL(node->right, key);
    else  // Duplicate keys not allowed in AVL tree
        return node;

    // Update the height of the ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether it became unbalanced
    int balance = getBalance(node);

    // If node becomes unbalanced, there are 4 cases:

    // Case 1 - Left Left (Rotate Right)
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // Case 2 - Right Right (Rotate Left)
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // Case 3 - Left Right (Left Rotate the Left Child, then Right Rotate)
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Case 4 - Right Left (Right Rotate the Right Child, then Left Rotate)
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Utility function to find the node with the minimum value (leftmost node)
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;

    // Loop down to find the leftmost leaf
    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Recursive function to delete a key from AVL tree
AVLNode* deleteAVL(AVLNode* root, int key) {
    // Perform standard BST delete
    if (root == nullptr)
        return root;

    // If key to be deleted is smaller than root's key, then it lies in the left subtree
    if (key < root->data)
        root->left = deleteAVL(root->left, key);

    // If key to be deleted is greater than root's key, then it lies in the right subtree
    else if (key > root->data)
        root->right = deleteAVL(root->right, key);

    // If key is the same as root's key, this is the node to be deleted
    else {
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AVLNode* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            delete temp;
        }
        else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AVLNode* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteAVL(root->right, temp->data);
        }
    }

    // If the tree had only one node, return
    if (root == nullptr)
        return root;

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this node
    int balance = getBalance(root);

    // If node becomes unbalanced, there are 4 cases:

    // Case 1 - Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Case 2 - Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Case 3 - Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Case 4 - Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to print the tree in-order (left -> root -> right)
void inorder(AVLNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Main function to test the AVL Tree implementation
int main() {
    AVLNode* root = nullptr;

    // Insert the input sequence into the AVL Tree
    int input[] = {16, 18, 12, 17, 9, 14, 19, 15, 11, 5, 3};
    int n = sizeof(input)/sizeof(input[0]);
    for (int i = 0; i < n; i++) {
        root = insertAVL(root, input[i]);
    }

    cout << "In-order traversal of the AVL tree after insertion: ";
    inorder(root);
    cout << endl;

    // Delete a few keys from the AVL tree
    root = deleteAVL(root, 14);
    root = deleteAVL(root, 9);

    cout << "In-order traversal of the AVL tree after deletion: ";
    inorder(root);
    cout << endl;

    return 0;
}
