#include "graph.h"

Graph::Graph(int n) {
    size = n;
    adjList.resize(n);
}

void Graph::addEdge(int u, int v, int w) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void Graph::removeEdge(int u, int v) {
    for (int i = 0; i < adjList[u].size(); i++) {
        if (adjList[u][i] == v) {
            adjList[u].erase(adjList[u].begin() + i);
            break;
        }
    }
    for (int i = 0; i < adjList[v].size(); i++) {
        if (adjList[v][i] == u) {
            adjList[v].erase(adjList[v].begin() + i);
            break;
        }
    }
}

void Graph::addVertex() {
    size++;
    adjList.resize(size);
}

void Graph::removeVertex(int u) {
    for (int i = 0; i < adjList[u].size(); i++) {
        int v = adjList[u][i];
        for (int j = 0; j < adjList[v].size(); j++) {
            if (adjList[v][j] == u) {
                adjList[v].erase(adjList[v].begin() + j);
                break;
            }
        }
    }
    adjList.erase(adjList.begin() + u);
    size--;
}

bool Graph::hasVertex(int u) const {
    return u >= 0 && u < size;
}

bool Graph::hasEdge(int u, int v) const {
    for (int i = 0; i < adjList[u].size(); i++) {
        if (adjList[u][i] == v) {
            return true;
        }
    }
    return false;
}

std::vector<int> Graph::getNeighbors(int u) const {
    return adjList[u];
}

int Graph::getWeight(int u, int v) const {
    for (int i = 0; i < adjList[u].size(); i++) {
        if (adjList[u][i] == v) {
            return 1;
        }
    }
    return 0;
}

int Graph::getSize() const {
    return size;
}