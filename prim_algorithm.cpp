#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
using namespace std;

// Function to find the vertex with the minimum key value
// that has not been included in the MST yet
int minKey(vector<int>& key, vector<bool>& mstSet, int V) {
    int min = INT_MAX, minIndex;

    // Iterate over all vertices
    for (int v = 0; v < V; v++) {
        // Find the smallest key value for a vertex not yet in the MST
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to print the edges of the Minimum Spanning Tree (MST)
void printMST(vector<int>& parent, vector<vector<int>>& graph, int V) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        // Print edges in the MST and their weights
        cout << parent[i] + 1 << " - " << i + 1 << "\t" << graph[i][parent[i]] << "\n";
    }
}

// Function to implement Prim's Algorithm
void primMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V);        // Array to store the MST
    vector<int> key(V, INT_MAX);  // Key values used to pick the minimum weight edge
    vector<bool> mstSet(V, false); // Boolean array to represent vertices included in the MST

    // Initialize the key value of the first vertex to 0
    key[0] = 0;
    parent[0] = -1; // The root node has no parent

    // Loop to build the MST
    for (int count = 0; count < V - 1; count++) {
        // Pick the vertex with the minimum key value that is not yet included in the MST
        int u = minKey(key, mstSet, V);
        mstSet[u] = true; // Mark the picked vertex as included in the MST

        // Update the key values and parent index of the adjacent vertices
        for (int v = 0; v < V; v++) {
            // Update the key only if:
            // 1. There is an edge from u to v.
            // 2. v is not in the MST.
            // 3. The weight of the edge u-v is smaller than the current key value of v.
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph, V);
}

int main() {
    // Number of vertices in the graph
    int V = 9;

    // Graph represented as an adjacency matrix
    vector<vector<int>> graph = {
        {0, 4, 0, 1, 0, 0, 0, 0, 0}, // Vertex 1
        {4, 0, 2, 0, 6, 0, 0, 0, 0}, // Vertex 2
        {0, 2, 0, 0, 0, 5, 0, 0, 2}, // Vertex 3
        {1, 0, 0, 0, 11, 0, 9, 0, 0}, // Vertex 4
        {0, 6, 0, 11, 0, 3, 0, 8, 0}, // Vertex 5
        {0, 0, 5, 0, 3, 0, 0, 0, 8}, // Vertex 6
        {0, 0, 0, 9, 0, 0, 0, 7, 0}, // Vertex 7
        {0, 0, 0, 0, 8, 0, 7, 0, 3}, // Vertex 8
        {0, 0, 2, 0, 0, 8, 0, 3, 0}  // Vertex 9
    };

    // Execute Prim's Algorithm
    primMST(graph, V);

    return 0;
}
