#ifndef FORD_FULKERSON_MAXIMUM_FLOW_H
#define FORD_FULKERSON_MAXIMUM_FLOW_H

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

class FordFulkersonMaximumFlow {
public:
    FordFulkersonMaximumFlow() = default;
    FordFulkersonMaximumFlow(const std::vector<std::vector<int>>& graph, int start_vertex, int end_vertex);

    void ford_fulkerson();
    void ford_fulkerson(const std::string& filename);

private:
    std::vector<std::vector<int>> m_graph;
    std::vector<std::vector<int>> m_residual_graph;
    std::vector<int> m_parent;
    std::vector<bool> m_visited;
    int m_start_vertex;
    int m_end_vertex;

    bool bfs();
    int find_min_residual_capacity();
    void update_residual_graph(int min_residual_capacity);
};

#endif // FORD_FULKERSON_MAXIMUM_FLOW_H