#include <iostream>      // For standard input/output
#include <vector>        // For using the vector container
#include <queue>         // For priority_queue
#include <utility>       // For using pairs (to store vertex-weight pairs)
#include <limits>        // For defining the infinite distance constant

using namespace std;

// Set a large constant value to represent infinity (unreachable nodes)
const int INF = numeric_limits<int>::max();

// Function to perform Dijkstra's algorithm on a graph represented as an adjacency list
void dijkstra(int start, vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();               // Number of vertices in the graph
    vector<int> distance(n, INF);       // Distance vector, initialized to infinity for all vertices
    vector<int> parent(n, -1);          // Parent vector to reconstruct the path (optional)
    distance[start] = 0;                // Distance to the start node is zero

    // Priority queue to choose the vertex with the smallest distance (min-heap)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});                // Push the start node with distance 0

    // Main loop: process nodes until all reachable nodes are visited
    while (!pq.empty()) {
        int dist = pq.top().first;      // Distance of the vertex with the smallest distance
        int u = pq.top().second;        // The vertex itself
        pq.pop();

        // If the distance is already greater, skip to the next vertex
        if (dist > distance[u]) continue;

        // Traverse all adjacent nodes (neighbors) of the current vertex u
        for (auto& edge : graph[u]) {
            int v = edge.first;         // Adjacent vertex
            int weight = edge.second;   // Edge weight

            // Relaxation step: check if we found a shorter path to v through u
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;  // Update the distance
                parent[v] = u;                       // Update the parent of v (for path reconstruction)
                pq.push({distance[v], v});           // Push updated distance to the priority queue
            }
        }
    }

    // Display the shortest distance from the starting vertex to each vertex
    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << "\t" << distance[i] << endl;
    }
}

// Main function to set up the graph and run Dijkstra’s algorithm
int main() {
    int n, m;  // n = number of vertices, m = number of edges
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    // Initialize the graph as an adjacency list: a vector of vectors of pairs
    vector<vector<pair<int, int>>> graph(n);

    cout << "Enter the edges (u, v, w) where u and v are vertices and w is the weight:" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;                // Input edge from u to v with weight w
        graph[u].push_back({v, w});        // Directed edge from u to v
        graph[v].push_back({u, w});        // For undirected graphs, also add edge from v to u
    }

    int start;
    cout << "Enter the starting vertex: ";
    cin >> start;

    // Run Dijkstra’s algorithm from the starting vertex
    dijkstra(start, graph);

    return 0;
}
