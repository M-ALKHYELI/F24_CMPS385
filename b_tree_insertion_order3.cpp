#include <iostream>
#include <vector>
using namespace std;

// Class representing a single node in the B-tree
class BTreeNode {
public:
    vector<int> keys;                // Vector to store keys
    vector<BTreeNode*> children;     // Vector of child pointers
    bool isLeaf;                     // True if node is a leaf

    // Constructor
    BTreeNode(bool isLeaf);
};

// Constructor for BTreeNode
BTreeNode::BTreeNode(bool isLeaf) {
    this->isLeaf = isLeaf;
}

// Class representing the B-tree itself
class BTree {
public:
    BTreeNode* root;     // Pointer to the root node
    int order;           // Order of the B-tree (maximum 2 keys for order 3)

    // Constructor
    BTree(int order);

    // Function to insert a key into the B-tree
    void insert(int key);

    // Helper function to insert a key into a non-full node
    void insertNonFull(BTreeNode* node, int key);

    // Helper function to split a full child of a node
    void splitChild(BTreeNode* parent, int index);

    // Helper function to print the structure of the tree
    void printTree(BTreeNode* node, int level);
};

// Constructor for BTree
BTree::BTree(int order) {
    this->order = order;
    root = new BTreeNode(true); // Start with an empty root node
}

// Insert function for BTree
void BTree::insert(int key) {
    // If the root is full, we need to split it and increase the height of the tree
    if (root->keys.size() == order - 1) {
        BTreeNode* newRoot = new BTreeNode(false); // Create a new root
        newRoot->children.push_back(root);         // Make the old root a child of the new root
        splitChild(newRoot, 0);                    // Split the old root
        root = newRoot;                            // Update root to the new root
        insertNonFull(newRoot, key);               // Insert the key in the new root
    } else {
        insertNonFull(root, key);                  // Insert the key in the current root if it's not full
    }
}

// Helper function to insert a key into a non-full node
void BTree::insertNonFull(BTreeNode* node, int key) {
    int i = node->keys.size() - 1; // Start from the last key in the node

    if (node->isLeaf) {
        // Insert the new key in the correct sorted position in the leaf node
        node->keys.push_back(0); // Add space for the new key
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i]; // Shift keys to the right to make space
            i--;
        }
        node->keys[i + 1] = key; // Insert the new key at the correct position
    } else {
        // Find the correct child to descend into
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++; // Move to the child that should contain the new key

        // If the child is full, split it first
        if (node->children[i]->keys.size() == order - 1) {
            splitChild(node, i); // Split the full child
            // After splitting, the middle key moves up, so adjust the child index if needed
            if (key > node->keys[i]) {
                i++;
            }
        }
        // Recursively insert the key into the appropriate child
        insertNonFull(node->children[i], key);
    }
}

// Helper function to split a full child of a given node
void BTree::splitChild(BTreeNode* parent, int index) {
    int mid = (order - 1) / 2; // Middle key to move up
    BTreeNode* child = parent->children[index];
    BTreeNode* newChild = new BTreeNode(child->isLeaf); // Create a new node for the split

    // Insert the middle key into the parent node
    parent->keys.insert(parent->keys.begin() + index, child->keys[mid]);

    // Split the keys of the child between itself and the new child
    newChild->keys.assign(child->keys.begin() + mid + 1, child->keys.end());
    child->keys.resize(mid);

    // If the child is not a leaf, split its children pointers as well
    if (!child->isLeaf) {
        newChild->children.assign(child->children.begin() + mid + 1, child->children.end());
        child->children.resize(mid + 1);
    }

    // Insert the new child in the parent's children list
    parent->children.insert(parent->children.begin() + index + 1, newChild);
}

// Helper function to print the structure of the B-tree
void BTree::printTree(BTreeNode* node, int level) {
    cout << "Level " << level << " Keys: ";
    for (int key : node->keys) {
        cout << key << " ";
    }
    cout << endl;

    // Recursively print all children
    if (!node->isLeaf) {
        for (BTreeNode* child : node->children) {
            printTree(child, level + 1); // Print each child at the next level
        }
    }
}

// Main function to demonstrate the B-tree insertion
int main() {
    BTree bTree(3); // Create a B-tree of order 3

    // Insert keys in the order given in the example
    vector<int> keys = {78, 52, 81, 40, 33, 90, 85, 20, 38};
    for (int key : keys) {
        bTree.insert(key);
    }

    // Print the structure of the B-tree after insertion
    bTree.printTree(bTree.root, 0);

    return 0;
}
