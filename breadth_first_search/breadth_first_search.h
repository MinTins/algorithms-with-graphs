#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include <vector>

class Graph {
public:
    Graph(int V);
    void addEdge(int v, int w);
    std::vector<int> BFS(int s);

private:
    int V;
    std::vector<std::vector<int>> adj;
};

#endif