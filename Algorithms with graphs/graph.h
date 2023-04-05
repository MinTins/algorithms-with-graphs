#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
    Graph(int n);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    void addVertex();
    void removeVertex(int u);
    bool hasVertex(int u) const;
    bool hasEdge(int u, int v) const;
    std::vector<int> getNeighbors(int u) const;
    int getWeight(int u, int v) const;
    int getSize() const;
private:
    std::vector<std::vector<int>> adjList;
    int size;
};

#endif