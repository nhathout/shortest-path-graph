#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>

using namespace std;

Graph::Graph() {
    numVertices = 0;
    numEdges = 0;
    adj = nullptr;
}

void Graph::initVertices(int V) {
    numVertices = V;
    adj = new vector<pair<int, int>>[V];
}

int Graph::getNumVertices() {
    return numVertices;
}

void Graph::setNumEdges(int E) {
    numEdges = E;
}

int Graph::getNumEdges() {
    return numEdges;
}

void Graph::addEdge(int v, int u, int weight) {
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        adj[v].push_back(make_pair(u, weight));
        adj[u].push_back(make_pair(v, weight));
        numEdges++;
    }
}

void Graph::print() {
    for (int v = 0; v < numVertices; v++) {
        cout << v << ": ";
        for (const auto& pair : adj[v]) {
            cout << pair.first << " (" << pair.second << ") ";
        }
        cout << endl;
    }
}

void Graph::generateGraph(string fileName) {
    fstream f;
    f.open(fileName, ios::in);

    if (f.is_open()) {
        string line;
        int numV, numE, u, v, w;
        int lines = 0;
        while (getline(f, line)) {
            istringstream iss(line);
            if (lines == 0) {
                iss >> numV >> numE;
                initVertices(numV);
                lines++;
            } else {
                iss >> u >> v >> w;
                addEdge(u, v, w);
            }
        }
    }
    f.close();
}

void Graph::numShortestPaths(int source) {
    vector<int> countV(numVertices, 0);
    vector<int> distance(numVertices, numeric_limits<int>::max());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    countV[source] = 1;
    distance[source] = 0;

    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int uVertex = pq.top().second;
        int runningDist = pq.top().first;
        pq.pop();

        if (runningDist > distance[uVertex]) {
            continue;
        }

        for (auto& pair : adj[uVertex]) {
            if (distance[pair.first] == distance[uVertex] + pair.second) {
                countV[pair.first] += countV[uVertex];
            } else if (distance[pair.first] > distance[uVertex] + pair.second) {
                distance[pair.first] = distance[uVertex] + pair.second;
                countV[pair.first] = countV[uVertex];
                pq.push(make_pair(distance[pair.first], pair.first));
            }
        }
    }

    cout << "\nShortest paths from node " << source << ": \n";
    for (int v = 0; v < numVertices; v++) {
        if (v != source) {
            cout << "Distance to vertex " << v << " is " << distance[v];
            cout << " and there are " << countV[v] << " shortest paths\n";
        }
    }
}
