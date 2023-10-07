#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

class Graph {
private:
    int V; // Number of vertices
    vector<Edge> edges;

public:
    Graph(int vertices) : V(vertices) {}

    // Add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    // Find the parent of a vertex using the union-find algorithm
    int findParent(vector<int> &parent, int vertex) {
        if (parent[vertex] == -1)
            return vertex;
        return findParent(parent, parent[vertex]);
    }

    // Perform union of two sets by rank
    void unionSets(vector<int> &parent, int x, int y) {
        int rootX = findParent(parent, x);
        int rootY = findParent(parent, y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }

    // Kruskal's algorithm to find the minimum spanning tree
    vector<Edge> kruskalMST() {
        vector<Edge> result; // To store the MST
        vector<int> parent(V, -1);

        // Sort edges in non-decreasing order of their weights
        sort(edges.begin(), edges.end());

        for (Edge edge : edges) {
            int rootSrc = findParent(parent, edge.src);
            int rootDest = findParent(parent, edge.dest);

            // If including this edge does not create a cycle, add it to the MST
            if (rootSrc != rootDest) {
                result.push_back(edge);
                unionSets(parent, rootSrc, rootDest);
            }
        }

        return result;
    }
};

int main() {
    // Create a graph with 4 vertices
    Graph graph(4);

    // Add edges to the graph
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    // Find and print the minimum spanning tree
    vector<Edge> mst = graph.kruskalMST();
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (Edge edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    }

    return 0;
}
