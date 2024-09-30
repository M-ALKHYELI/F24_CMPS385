#include <iostream>
#include <string>

using namespace std;

// Structure for a Tree Node to represent a directory or file
struct TreeNode {
    string name;           // Name of the directory or file
    bool isDirectory;      // Flag to check if the node is a directory
    int size;              // Size of the file (0 if it's a directory)
    TreeNode* firstChild;  // Pointer to the first child (subdirectory or file)
    TreeNode* nextSibling; // Pointer to the next sibling (in the same directory)
    
    // Constructor to initialize a TreeNode
    TreeNode(string n, bool isDir, int s = 0) : name(n), isDirectory(isDir), size(s), firstChild(NULL), nextSibling(NULL) {}
};

// Function to print the name of a directory or file with indentation
void printName(TreeNode* t, int depth) {
    for (int i = 0; i < depth; ++i)
        cout << "\t"; // Print indentation based on depth
    cout << t->name << endl; // Print the name of the file or directory
}

// Function to check if the current node is a directory
bool isDirectory(TreeNode* t) {
    return t->isDirectory;
}

// 2.1 Function to list all files and directories (pre-order traversal)
void listAll(TreeNode* t, int depth) {
    // Print the current directory/file name with the appropriate depth
    printName(t, depth);
    
    // If the current node is a directory, list its children
    if (isDirectory(t)) {
        TreeNode* child = t->firstChild;
        while (child != NULL) {
            // Recursively call listAll for each child with increased depth
            listAll(child, depth + 1);
            child = child->nextSibling;
        }
    }
}

// 2.2 Function to calculate the total size of a directory (post-order traversal)
int size(TreeNode* t) {
    // Start with the size of the current node (file or directory)
    int totalSize = t->size;
    
    // If the current node is a directory, recursively calculate the size of its children
    if (isDirectory(t)) {
        TreeNode* child = t->firstChild;
        while (child != NULL) {
            // Add the size of each child to totalSize
            totalSize += size(child);
            child = child->nextSibling;
        }
    }
    
    // Return the total size of the directory or file
    return totalSize;
}

// Helper function to add a file or subdirectory to a directory
void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->firstChild == NULL) {
        parent->firstChild = child; // Add as the first child if no child exists
    } else {
        TreeNode* sibling = parent->firstChild;
        // Find the last sibling and add the new child as its sibling
        while (sibling->nextSibling != NULL) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = child;
    }
}

int main() {
    // Create a simple file system structure for demonstration
    TreeNode* root = new TreeNode("root", true);  // Root directory
    
    // Adding directories and files under the root
    TreeNode* dirA = new TreeNode("dirA", true);
    TreeNode* fileA1 = new TreeNode("fileA1.txt", false, 50);  // File with size 50
    TreeNode* fileA2 = new TreeNode("fileA2.txt", false, 30);  // File with size 30
    
    TreeNode* dirB = new TreeNode("dirB", true);
    TreeNode* fileB1 = new TreeNode("fileB1.txt", false, 100); // File with size 100
    
    // Build the tree structure
    addChild(root, dirA); // Add dirA to root
    addChild(root, dirB); // Add dirB to root
    addChild(dirA, fileA1); // Add fileA1 to dirA
    addChild(dirA, fileA2); // Add fileA2 to dirA
    addChild(dirB, fileB1); // Add fileB1 to dirB

    // List all directories and files
    cout << "Directory Listing:" << endl;
    listAll(root, 0);
    
    // Calculate the total size of the directory
    cout << "\nTotal Size of the root directory: " << size(root) << " bytes" << endl;

    // Clean up (deleting nodes)
    delete fileA1;
    delete fileA2;
    delete fileB1;
    delete dirA;
    delete dirB;
    delete root;

    return 0;
}
