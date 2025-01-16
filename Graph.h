#ifndef Graph_h
#define Graph_h

#include <vector>
#include <string>
#include <utility>

using namespace std;

/* Implements an undirected, weighted graph */
class Graph {
public:
    Graph(); // Constructs an empty graph
    void initVertices(int V); // Initializes the graph with V vertices
    int getNumVertices(); // Returns the number of vertices
    void setNumEdges(int E); // Sets the number of edges
    int getNumEdges(); // Returns the number of edges
    void addEdge(int v, int u, int weight); // Adds an edge with weight
    void print(); // Prints the adjacency list
    void generateGraph(string fileName); // Constructs graph from input file
    void numShortestPaths(int source); // Prints shortest paths and their weights

private:
    int numVertices; // Number of vertices
    int numEdges; // Number of edges
    vector<pair<int, int>> *adj; // Adjacency list
};

#endif
