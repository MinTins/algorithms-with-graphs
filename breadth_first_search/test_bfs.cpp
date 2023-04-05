#include "breadth_first_search.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void testBFS(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return;
    }

    int V, E, s;
    file >> V >> E >> s;

    Graph g(V);

    int v, w;
    for (int i = 0; i < E; i++) {
        file >> v >> w;
        g.addEdge(v, w);
    }

    std::vector<int> result = g.BFS(s);

    std::cout << "BFS starting from vertex " << s << ": ";
    for (auto i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    file.close();
}