#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

// Adjacency matrix to represent connections between graph nodes
std::vector<std::vector<int>> edges;

// Vector to keep track of the number of neighbors for each node
std::vector<int> neighbor;


int n, best;

void unsocialNetwork(int v, int size) {
    // Variable to calculate the upper bound of unvisited neighbors
    int UB = 0;

    // Update the maximum size found
    if (size > best) {
        best = size;
    }

    // Calculate the upper bound of unvisited neighbors
    for (int i = v + 1; i < n; i++) {
        if (neighbor[i] == 0) {
            UB++;
        }
    }

    // If the current size plus the number of unvisited neighbors is less than or equal to the best found, return
    if (size + UB <= best) {
        return;
    }

    // Update neighbors for the current node
    for (int i = v + 1; i < n; i++) {
        if (edges[i][v] == 1) {
            neighbor[i]++;
        }
    }

    // Explore unvisited neighbors recursively
    for (int i = v + 1; i < n; i++) {
        if (neighbor[i] == 0) {
            unsocialNetwork(i, size + 1);
        }
    }

    // Undo changes to neighbors after exploring the node
    for (int i = v + 1; i < n; i++) {
        if (edges[i][v] == 1) {
            neighbor[i]--;
        }
    }
}

int main() {
    int m;
    int node1, node2;

    
    std::cin >> n >> m;

    // Initialize the adjacency matrix with zeros
    edges = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));

    // Fill the adjacency matrix with the provided edges
    for (int i = 0; i < m; i++) {
        std::cin >> node1 >> node2;
        edges[node1][node2] = 1;
        edges[node2][node1] = 1; // The graph is undirected, so edges are bidirectional
    }

    // Initialize the neighbor vector with zeros
    for (int i = 0; i < n; i++) {
        neighbor.push_back(0);
    }

    // Call the function to find the largest unsocial network for each node
    for (int i = 0; i < n; i++) {
        unsocialNetwork(i, 1);
    }

   
    std::cout << best << "\n";
}
