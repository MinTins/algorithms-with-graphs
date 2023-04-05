#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

class BreadthFirstSearch {
public:
    BreadthFirstSearch() = default;
    BreadthFirstSearch(const std::vector<std::vector<int>>& graph, int start_vertex);

    void bfs();
    void bfs(const std::string& filename);

private:
    std::vector<std::vector<int>> m_graph;
    std::vector<bool> m_visited;
    std::queue<int> m_queue;
    int m_start_vertex;
};

#endif // BREADTH_FIRST_SEARCH_H