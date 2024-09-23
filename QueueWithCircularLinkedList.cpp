#include <iostream>
using namespace std;

// Node structure for the circular linked list
template <class T>
class QueueNode {
public:
    T item;               // Data stored in the node
    QueueNode* next;      // Pointer to the next node

    // Constructor to initialize a node
    QueueNode(const T& e = T(), QueueNode* n = nullptr) : item(e), next(n) {}
};

// Queue class using a circular linked list with one external pointer (backPtr)
template <class T>
class Queue {
public:
    // Constructor: Initializes an empty queue
    Queue();

    // Destructor: Deallocates all nodes to avoid memory leaks
    ~Queue();

    // Checks if the queue is empty
    bool isEmpty() const;

    // Enqueues a new item at the rear (back) of the queue
    void enqueue(const T& newItem);

    // Dequeues the front item and stores it in queueFront
    void dequeue(T& queueFront);

    // Retrieves the front item without removing it
    void getFront(T& queueFront) const;

private:
    QueueNode<T>* backPtr;  // Pointer to the back of the queue
};

// Constructor: Initializes the queue to an empty state
template <class T>
Queue<T>::Queue() : backPtr(nullptr) {}

// Destructor: Frees all nodes in the queue
template <class T>
Queue<T>::~Queue() {
    while (!isEmpty()) {   // Dequeue until the queue is empty
        T frontItem;
        dequeue(frontItem);   // Dequeue and delete the front item
    }
}

// Checks if the queue is empty by checking if backPtr is nullptr
template <class T>
bool Queue<T>::isEmpty() const {
    return backPtr == nullptr;
}

// Enqueue: Adds a new item to the back of the circular queue
template <class T>
void Queue<T>::enqueue(const T& newItem) {
    QueueNode<T>* newPtr = new QueueNode<T>(newItem);

    if (isEmpty()) {
        // If the queue is empty, the new node points to itself (circular nature)
        newPtr->next = newPtr;
        backPtr = newPtr;  // Both front and back are the same
    } else {
        // Insert the new node after the back node and update pointers
        newPtr->next = backPtr->next;   // New node points to the front node
        backPtr->next = newPtr;         // Back node points to the new node
        backPtr = newPtr;               // Update backPtr to the new node
    }
}

// Dequeue: Removes the front item from the queue and stores it in queueFront
template <class T>
void Queue<T>::dequeue(T& queueFront) {
    if (isEmpty()) {
        throw runtime_error("Queue is empty. Cannot dequeue.");
    } else {
        // The front node is the node after backPtr
        QueueNode<T>* frontPtr = backPtr->next;
        queueFront = frontPtr->item;  // Get the front item

        if (backPtr == frontPtr) {
            // If the queue has only one node, remove it and set the queue to empty
            delete frontPtr;
            backPtr = nullptr;
        } else {
            // More than one node: adjust backPtr and delete the front node
            backPtr->next = frontPtr->next;
            delete frontPtr;
        }
    }
}

// GetFront: Retrieves the front item without removing it from the queue
template <class T>
void Queue<T>::getFront(T& queueFront) const {
    if (isEmpty()) {
        throw runtime_error("Queue is empty. Cannot get front.");
    } else {
        // The front node is the node after backPtr
        QueueNode<T>* frontPtr = backPtr->next;
        queueFront = frontPtr->item;  // Retrieve the front item
    }
}

// Main function to demonstrate the circular queue operations
int main() {
    Queue<int> q;  // Create a queue of integers

    // Enqueue some values
    q.enqueue(2);
    q.enqueue(4);
    q.enqueue(1);
    q.enqueue(7);

    // Display the front item
    int front;
    q.getFront(front);
    cout << "Front item: " << front << endl;  // Should print 2

    // Dequeue and display the front item
    q.dequeue(front);
    cout << "Dequeued item: " << front << endl;  // Should print 2

    // Get the new front item
    q.getFront(front);
    cout << "New front item: " << front << endl;  // Should print 4

    // Continue dequeuing
    q.dequeue(front);
    cout << "Dequeued item: " << front << endl;  // Should print 4

    return 0;
}
