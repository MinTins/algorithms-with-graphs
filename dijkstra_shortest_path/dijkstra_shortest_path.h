#ifndef DIJKSTRA_SHORTEST_PATH_H
#define DIJKSTRA_SHORTEST_PATH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

class DijkstraShortestPath {
public:
    DijkstraShortestPath() = default;
    DijkstraShortestPath(const std::vector<std::vector<std::pair<int, int>>>& graph, int start_vertex);

    void shortest_path();
    void shortest_path(const std::string& filename);

private:
    std::vector<std::vector<std::pair<int, int>>> m_graph;
    std::vector<int> m_distance;
    std::vector<bool> m_visited;
    int m_start_vertex;
};

#endif // DIJKSTRA_SHORTEST_PATH_H