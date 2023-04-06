#ifndef PRIM_MINIMUM_SPANNING_TREE_H
#define PRIM_MINIMUM_SPANNING_TREE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

class PrimMinimumSpanningTree {
public:
    PrimMinimumSpanningTree() = default;
    PrimMinimumSpanningTree(const std::vector<std::vector<std::pair<int, int>>>& graph, int start_vertex);
    void prim();
    void prim(const std::string& filename);

private:
    std::vector<std::vector<std::pair<int, int>>> m_graph;
    std::vector<bool> m_visited;
    std::vector<int> m_min_distance;
    std::vector<int> m_vertex;
    int m_start_vertex;
};

#endif // PRIM_MINIMUM_SPANNING_TREE_H