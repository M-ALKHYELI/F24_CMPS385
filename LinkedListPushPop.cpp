#include <iostream>
using namespace std;

// Node structure representing a single element in the linked list
struct Node {
    int data;       // Data part of the node
    Node* next;     // Pointer to the next node in the list
};

// Class representing a singly linked list
class SinglyLinkedList {
private:
    Node* head;     // Pointer to the head (first node) of the list

public:
    // Constructor initializes the head of the list to NULL (empty list)
    SinglyLinkedList() : head(NULL) {}

    // Function to push a new value onto the list (insert at the beginning)
    void Push(int value) {
        // Create a new node
        Node* newNode = new Node();
        newNode->data = value;
        // Set the next of the new node to the current head
        newNode->next = head;
        // Move the head pointer to the new node (new node becomes the first node)
        head = newNode;

        // Print a message indicating the value has been pushed onto the list
        cout << "Pushed " << value << " onto the list." << endl;
    }

    // Function to return the value of the top node and remove it from the list
    int TopandPop() {
        // If the list is empty, we can't pop, so we return -1 as an error indicator
        if (head == NULL) {
            cout << "The list is empty. Cannot pop." << endl;
            return -1;
        }

        // Get the data from the head (top) node
        int topValue = head->data;

        // Move the head pointer to the next node (removing the current head)
        Node* temp = head;
        head = head->next;

        // Free the memory of the old head node
        delete temp;

        // Return the value of the popped node
        cout << "Popped " << topValue << " from the list." << endl;
        return topValue;
    }

    // Destructor to clean up the list and prevent memory leaks
    ~SinglyLinkedList() {
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    // Create a singly linked list object
    SinglyLinkedList list;

    // Push some values onto the list
    list.Push(10);  // Push 10 onto the list
    list.Push(20);  // Push 20 onto the list
    list.Push(30);  // Push 30 onto the list

    // Pop the top value and display it
    list.TopandPop();  // Should pop 30
    list.TopandPop();  // Should pop 20

    // Try popping again
    list.TopandPop();  // Should pop 10

    // Attempt to pop from an empty list
    list.TopandPop();  // Should indicate the list is empty

    return 0;
}
