#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

class DepthFirstSearch {
public:
    DepthFirstSearch() = default;
    DepthFirstSearch(const std::vector<std::vector<int>>& graph, int start_vertex);
    void dfs();
    void dfs(const std::string& filename);

private:
    std::vector<std::vector<int>> m_graph;
    std::vector<bool> m_visited;
    std::stack<int> m_stack;
    int m_start_vertex;
};

#endif // DEPTH_FIRST_SEARCH_H