#include <iostream>
#include "graph.h"

int main() {
    Graph g(4);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 2);
    std::cout << "Graph size: " << g.getSize() << std::endl;
    std::cout << "Vertex 2 has neighbors: ";
    std::vector<int> neighbors = g.getNeighbors(2);
    for (int i = 0; i < neighbors.size(); i++) {
        std::cout << neighbors[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Edge between vertices 1 and 2: " << g.hasEdge(1, 2) << std::endl;
    g.removeVertex(2);
    std::cout << "Graph size after removing vertex 2: " << g.getSize() << std::endl;
    std::cout << "Vertex 1 has neighbors: ";
    neighbors = g.getNeighbors(1);
    for (int i = 0; i < neighbors.size(); i++) {
        std::cout << neighbors[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Edge between vertices 1 and 2 after removing vertex 2: "<< g.hasEdge(1, 2) << std::endl;

    return 0;
}